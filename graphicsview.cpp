#include "graphicsview.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget *parent)
    : m_scale(1),
    m_position(QPointF(0, 0)),
    m_positionAnimation(nullptr),
    QWidget{parent}
{
    m_svgRenderer = new QSvgRenderer(this);
    m_svgRenderer->load(QString(":/graphics/resources/helicopter-svgrepo-com.svg"));

    QObject::connect(this, &GraphicsView::scaleChanged, this, [=]() {
        this->update();
    });
    QObject::connect(this, &GraphicsView::positionChanged, this, [=]() {
        this->update();
    });
    QObject::connect(this, &GraphicsView::angleChanged, this, [=]() {
        this->update();
    });
}

void GraphicsView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    auto size = this->size();
    painter.fillRect(QRect(0, 0, size.width(), size.height()), QColor(200, 160, 140));

    // draw the svg
    auto svgSize = m_svgRenderer->defaultSize();
    auto svgAspectRatio = svgSize.width() / svgSize.height();
    double widgetAspectRatio = static_cast<double>(size.width()) / size.height();

    painter.save();
    painter.translate(QPointF(size.width() / 2, size.height() / 2));
    painter.scale(m_scale, m_scale);
    painter.rotate(m_angle);
    painter.translate(QPointF(-size.width() / 2, -size.height() / 2));

    painter.translate(m_position);

    QRectF targetRect;
    if (widgetAspectRatio > svgAspectRatio) {
        // The widget is wider relative to its height than the SVG, so scale based on height
        double scaledWidth = svgAspectRatio * size.height();
        targetRect = QRectF((size.width() - scaledWidth) / 2, 0, scaledWidth, size.height());
    } else {
        // The widget is taller relative to its width than the SVG, so scale based on width
        qreal scaledHeight = size.width() / svgAspectRatio;
        targetRect = QRectF(0, (size.height() - scaledHeight) / 2, size.width(), scaledHeight);
    }
    m_svgRenderer->render(&painter, targetRect);
    painter.restore();

    // draw some text
    painter.setFont(QFont("Sans", 72, QFont::ExtraBold));
    painter.setPen(QColor(40, 40, 40, 180));
    painter.drawText(20, 120, QString("Helicopter SVG"));
}

void GraphicsView::setPositionAnimated(QPointF position, int duration)
{
    if (m_positionAnimation != nullptr) {
        delete m_positionAnimation;
    }
    m_positionAnimation = new QPropertyAnimation(this, "position", this);
    m_positionAnimation->setStartValue(m_position);
    m_positionAnimation->setEndValue(position);
    m_positionAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_positionAnimation->setDuration(duration);
    m_positionAnimation->start();
}

void GraphicsView::setAngleAnimated(double angle, int duration, std::function<void()> onFinished)
{
    if (m_angleAnimation != nullptr) {
        delete m_angleAnimation;
    }
    m_angleAnimation = new QPropertyAnimation(this, "angle", this);
    m_angleAnimation->setStartValue(m_angle);
    m_angleAnimation->setEndValue(angle);
    m_angleAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_angleAnimation->setDuration(duration);
    m_angleAnimation->start();
    if (onFinished != nullptr) {
        m_angleAnimation->connect(m_angleAnimation, &QPropertyAnimation::finished, this, [=]() {
            onFinished();
        });
    }
}

static double signum(double n) { return n > 0 ? 1 : n < 0 ? -1 : 0; }

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    auto deltaDegrees = event->angleDelta();
    setScale(scale() + signum(deltaDegrees.y()) * 0.1);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    static int count = 0;
    if (count % 2 == 0) {
        // fly out
        setPositionAnimated(QPointF(-size().width() * 2, -200));
        setAngleAnimated(30, 1500, [=]() {
            setAngleAnimated(0, 1500);
        });
    } else {
        setPositionAnimated(QPointF(0, 0), 400);
        setAngleAnimated(0, 400);
    }
    count++;
}

