#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QGraphicsView>
#include "Menu.h"

class GameManager : public QGraphicsView {

public:

    GameManager(QWidget* parent=nullptr);

    void run();

private:

    QGraphicsScene* scene;
    Menu* menu;

};

#endif // GAMEMANAGER_H
