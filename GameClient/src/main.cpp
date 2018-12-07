#include <QApplication>
#include "GameManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameManager* game = new GameManager();
    game->show();
    game->run();

    return a.exec();
}
