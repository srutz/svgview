#include "graphicsview.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QWheelEvent>

GraphicsView::GraphicsView(QWidget *parent)
    :
    QWidget{parent}
{
    m_svgRenderer = new QSvgRenderer(this);
    m_svgRenderer->load(QString(":/graphics/resources/helicopter-svgrepo-com.svg"));
    m_animatedItem = new AnimatedItem(this);

    QObject::connect(m_animatedItem, &AnimatedItem::changed, this, [=]() {
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
    m_animatedItem->draw(painter, size, [=](QPainter& painter) {
        m_svgRenderer->render(&painter, targetRect);
    });

    // draw some text
    painter.setFont(QFont("Sans", 72, QFont::ExtraBold));
    painter.setPen(QColor(40, 40, 40, 180));
    painter.drawText(20, 120, QString("Helicopter SVG"));
}


static double signum(double n) { return n > 0 ? 1 : n < 0 ? -1 : 0; }

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    auto deltaDegrees = event->angleDelta();
    m_animatedItem->setScaleAnimated(m_animatedItem->scale() + signum(deltaDegrees.y()) * 0.2, 200);
}

void GraphicsView::mousePressEvent(QMouseEvent *event)
{
    static int count = 0;
    if (count % 2 == 0) {
        // fly out
        m_animatedItem->setPositionAnimated(QPointF(-size().width() * 2, -200));
        m_animatedItem->setAngleAnimated(30, 1000, [=]() {
            m_animatedItem->setAngleAnimated(0, 1500);
        });
    } else {
        // reset
        m_animatedItem->setPositionAnimated(QPointF(0, 0), 400);
        m_animatedItem->setAngleAnimated(0, 400);
    }
    count++;
}

