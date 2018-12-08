#ifndef MENU_H
#define MENU_H

#include <QLineEdit>
#include <QLabel>
#include <thrift/transport/TSocket.h>
#include <thrift/protocol/TCompactProtocol.h>
#include "Lobby.h"

class Menu : public QObject {
    Q_OBJECT
public:

    Menu(QGraphicsScene* ptr, QWidget* parent);

public slots:

    void display_main_menu();

private:

    QGraphicsScene* mScene;
    QWidget* mParent;
    boost::shared_ptr<apache::thrift::transport::TTransport> socket;
    boost::shared_ptr<apache::thrift::transport::TTransport> transport;
    boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol;
    GameLobbyClient client;
    QLineEdit* editUsername;
    QLineEdit* editPassword;
    QLineEdit* editPasswordConfirm;
    Lobby* mLobby;

private slots:

    void signin_menu();
    void signup_menu();
    void sign_in(const std::string& username, const std::string& password);
    void sign_up(const std::string& username, const std::string& password, const std::string& password_confirm);
};

#endif // MENU_H
