#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <iostream>
#include <QGraphicsScene>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include "CGS/CardGame.h"
#include "GLS/GameLobby.h"
#include "Button.h"

class TableManager : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:

    TableManager(QGraphicsScene* ptr, const Game g, const int id, QGraphicsPixmapItem* parent = nullptr);

    void upate_slots(std::vector<bool>& slots);

private:

    QGraphicsScene* mScene;
    Game mGame;
    int mId;

private slots:

    void pick_slot(int i);
};

#endif // TABLE_H
