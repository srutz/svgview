#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QWidget>

class GraphicsView : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QPointF position READ position WRITE setPosition NOTIFY positionChanged)
    Q_PROPERTY(double angle READ angle WRITE setAngle NOTIFY angleChanged)

    QSvgRenderer *m_svgRenderer;
    double m_scale;
    
    double m_angle = 0;
    QPropertyAnimation *m_angleAnimation = nullptr;

    QPointF m_position;
    QPropertyAnimation *m_positionAnimation = nullptr;

signals:
    void scaleChanged(double);
    void positionChanged(QPointF);
    void angleChanged(double);

public:
    explicit GraphicsView(QWidget *parent = nullptr);

    double scale() const { return m_scale; }
    void setScale(double s) { if (m_scale == s) return; m_scale = s; emit scaleChanged(m_scale); }
    QPointF position() const { return m_position; }
    void setPosition(QPointF p) { if (m_position == p) return; m_position= p; emit positionChanged(m_position); }
    double angle() const { return m_angle; }
    void setAngle(double a)
    { 
        if (m_angle == a) return; 
        m_angle = a; 
        emit angleChanged(m_angle); 
    }

    void setPositionAnimated(QPointF position, int duration = 5000);
    void setAngleAnimated(double angle, int duration = 5000, std::function<void()> onFinished = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // GRAPHICSVIEW_H
