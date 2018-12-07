#include "GameManager.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::shared_ptr;

GameManager::GameManager(QWidget *parent) {

    // Base game window
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    // Game scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1024, 768);
    setScene(scene);

    menu = new Menu(scene, parent);
}

void GameManager::run() {

    menu->display_main_menu();
}
