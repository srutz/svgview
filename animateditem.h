#ifndef ANIMATEDITEM_H
#define ANIMATEDITEM_H

/* an animated item can paint itself into 
 * a QPainter object and also has methods
 * to animated scale, position and angle
 */

#include <QObject>
#include <QPainter>
#include <QPointF>
#include <QPropertyAnimation>

class AnimatedItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(double angle READ angle WRITE setAngle NOTIFY angleChanged)

    double m_scale = 1;
    QPropertyAnimation *m_scaleAnimation = nullptr;

    double m_angle = 0;
    QPropertyAnimation *m_angleAnimation = nullptr;

    QPointF m_position{ 0, 0 };
    QPropertyAnimation *m_positionAnimation = nullptr;


public:
    AnimatedItem(QObject *parent = nullptr);

    double scale() const { return m_scale; }
    void setScale(double s);

    QPointF position() const { return m_position; }
    void setPosition(QPointF p);

    double angle() const { return m_angle; }
    void setAngle(double a);

    void setScaleAnimated(double, int duration = 5000, std::function<void()> onFinished = nullptr);
    void setPositionAnimated(QPointF, int duration = 5000, std::function<void()> onFinished = nullptr);
    void setAngleAnimated(double, int duration = 5000, std::function<void()> onFinished = nullptr);

    void draw(QPainter& painter, const QSize &size, std::function<void(QPainter&)>);

signals:

    void scaleChanged(double);
    void positionChanged(QPointF);
    void angleChanged(double);
    void changed();

};

#endif // ANIMATEDITEM_H
