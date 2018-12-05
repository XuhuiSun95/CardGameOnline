#ifndef CARD_H
#define CARD_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

class Card : public QGraphicsPixmapItem {

public:

    Card(QString name, QGraphicsPixmapItem* parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:

    bool choosed;
    QGraphicsRectItem* rect;

};

#endif // CARD_H
