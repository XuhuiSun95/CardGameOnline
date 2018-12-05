#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLineEdit>
#include <QLabel>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TCompactProtocol.h>
#include "Button.h"
#include "Card.h"
#include "GLS/GameLobby.h"

class GameManager : public QGraphicsView {
    Q_OBJECT
public:

    GameManager(QWidget* parent=nullptr);

    void start();

public slots:

    void displayMainMenu();
    void signinMenu();
    void signupMenu();
    void sign_in(const std::string& username, const std::string& password);
    void sign_up(const std::string& username, const std::string& password, const std::string& password_confirm);

private:

    QGraphicsScene* scene;
    boost::shared_ptr<apache::thrift::transport::TTransport> socket;
    boost::shared_ptr<apache::thrift::transport::TTransport> transport;
    boost::shared_ptr<apache::thrift::protocol::TProtocol> protocol;
    GameLobbyClient client;
    QLineEdit* editUsername;
    QLineEdit* editPassword;
    QLineEdit* editPasswordConfirm;

};

#endif // GAME_H
