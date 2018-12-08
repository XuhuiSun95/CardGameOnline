#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsTextItem>
#include <QBrush>

class Button : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:

    Button(QString name, int width, const int height, QGraphicsRectItem* parent=nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);

signals:

    void clicked();

private:

    QGraphicsTextItem* text;

};

#endif // BOTTON_H
