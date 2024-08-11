#include "animateditem.h"

AnimatedItem::AnimatedItem(QObject *parent) : QObject(parent) {

}

void AnimatedItem::setScale(double s)
{
    if (m_scale == s) return;
    m_scale = s;
    emit scaleChanged(s);
    emit changed();
}

void AnimatedItem::setPosition(QPointF p)
{
    if (m_position == p) return;
    m_position= p;
    emit positionChanged(p);
    emit changed();
}

void AnimatedItem::setAngle(double a)
{
    if (m_angle == a) return;
    m_angle = a;
    emit angleChanged(a);
    emit changed();
}


void AnimatedItem::setScaleAnimated(double scale, int duration, std::function<void()> onFinished)
{
    if (m_scaleAnimation != nullptr) {
        delete m_scaleAnimation;
    }
    m_scaleAnimation = new QPropertyAnimation(this, "scale", this);
    m_scaleAnimation->setStartValue(m_scale);
    m_scaleAnimation->setEndValue(scale);
    m_scaleAnimation->setEasingCurve(QEasingCurve::InOutQuad);
    m_scaleAnimation->setDuration(duration);
    m_scaleAnimation->start();
    if (onFinished != nullptr) {
        m_scaleAnimation->connect(m_scaleAnimation, &QPropertyAnimation::finished, this, [=]() {
            onFinished();
        });
    }
}

void AnimatedItem::setPositionAnimated(QPointF position, int duration, std::function<void()> onFinished)
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
    if (onFinished != nullptr) {
        m_positionAnimation->connect(m_positionAnimation, &QPropertyAnimation::finished, this, [=]() {
            onFinished();
        });
    }
}

void AnimatedItem::setAngleAnimated(double angle, int duration, std::function<void()> onFinished)
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

void AnimatedItem::draw(QPainter& painter, const QSize &size, std::function<void(QPainter&)> f) {
    painter.save();
    painter.translate(QPointF(size.width() / 2, size.height() / 2));
    painter.scale(m_scale, m_scale);
    painter.rotate(m_angle);
    painter.translate(QPointF(-size.width() / 2, -size.height() / 2));
    painter.translate(m_position);
    f(painter);
    painter.restore();

}

