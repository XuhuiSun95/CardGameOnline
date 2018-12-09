#ifndef CARDMANAGER_H
#define CARDMANAGER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

class CardManager : public QGraphicsPixmapItem {

public:

    CardManager(QString name, QGraphicsPixmapItem* parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

private:

    bool choosed;
    QGraphicsRectItem* rect;

};

#endif // CARD_H
