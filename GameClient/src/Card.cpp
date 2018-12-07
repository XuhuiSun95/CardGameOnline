#include "Card.h"

Card::Card(QString name, QGraphicsPixmapItem* parent) : QGraphicsPixmapItem (parent) {

    // Base card pixmap
    choosed = false;
    QString path = ":/images/images/" + name + ".png";
    setPixmap(QPixmap(path));

    // Card choosed rect
    rect = new QGraphicsRectItem(boundingRect(), this);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    rect->setBrush(brush);
    rect->setOpacity(0.0);

    // Card setting
    setAcceptHoverEvents(true);
}

void Card::mousePressEvent(QGraphicsSceneMouseEvent* event) {

    if(choosed) {
        choosed = false;
        setPos(x(), y()+10);
    } else {
        choosed = true;
        setPos(x(), y()-10);
    }
}

void Card::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {

    rect->setOpacity(0.3);
}

void Card::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {

    rect->setOpacity(0.0);
}
