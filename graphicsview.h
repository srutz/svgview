#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include "animateditem.h"

#include <QPropertyAnimation>
#include <QSvgRenderer>
#include <QWidget>

class GraphicsView : public QWidget
{
    Q_OBJECT

    QSvgRenderer *m_svgRenderer;
    AnimatedItem* m_animatedItem;

signals:

public:
    explicit GraphicsView(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

};

#endif // GRAPHICSVIEW_H
