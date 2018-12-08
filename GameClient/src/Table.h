#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <QGraphicsScene>
#include "Button.h"

class Table : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:

    Table(QGraphicsScene* ptr, const int id, QGraphicsPixmapItem* parent = nullptr);

    void upate_slots(std::vector<bool>& slots);

private:

    QGraphicsScene* mScene;
    int mId;

private slots:

    void pick_slot(int i);
};

#endif // TABLE_H
