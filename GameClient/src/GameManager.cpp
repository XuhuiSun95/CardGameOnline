#include "GameManager.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::shared_ptr;

GameManager::GameManager(QWidget *parent) :
    socket(new TSocket("localhost", 9001)),
    transport(new TFramedTransport(socket)),
    protocol(new TCompactProtocol(transport)),
    client(protocol) {

    // Base game window
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024, 768);

    // Game scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1024, 768);
    setScene(scene);
}

void GameManager::displayMainMenu() {

    // Clear all
    scene->clear();

    // Menu title
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Card Game Online"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    double txPos = width()/2 - titleText->boundingRect().width()/2;
    double tyPos = height()/5;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the sign_in button
    Button* signinButton = new Button(QString("Sign in"));
    double ixPos = width()/2 - signinButton->boundingRect().width()/2;
    double iyPos = height()/10*5;
    signinButton->setPos(ixPos,iyPos);
    connect(signinButton, &Button::clicked, this, [this]{ signinMenu(); });
    scene->addItem(signinButton);

    // create the sign_up button
    Button* signupButton = new Button(QString("Sign up"));
    double uxPos = width()/2 - signupButton->boundingRect().width()/2;
    double uyPos = height()/10*6;
    signupButton->setPos(uxPos,uyPos);
    connect(signupButton, &Button::clicked, this, [this]{ signupMenu(); });
    scene->addItem(signupButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    double qxPos = width()/2 - quitButton->boundingRect().width()/2;
    double qyPos = height()/10*7;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, &Button::clicked, this, [this]{ close(); });
    scene->addItem(quitButton);
}

void GameManager::signinMenu() {

    // Clear all
    scene->clear();

    // initialize the username combo box so that it is editable
    editUsername = new QLineEdit();
    editUsername->setEchoMode(QLineEdit::Normal);
    int uxPos = width()/2;
    int uyPos = height()/10*3;
    editUsername->setGeometry(uxPos, uyPos, 300, 35);
    scene->addWidget(editUsername);
    // initialize the password field so that it does not echo characters
    editPassword = new QLineEdit();
    editPassword->setEchoMode(QLineEdit::Password);
    int pyPos = height()/10*4;
    editPassword->setGeometry(uxPos, pyPos, 300, 35);
    scene->addWidget(editPassword);

    // initialize the labels
    QFont font("MV Boli", 15, QFont::Bold);
    QLabel* labelUsername = new QLabel();
    QLabel* labelPassword = new QLabel();
    labelUsername->setFont(font);
    labelUsername->setText(QString("Username"));
    labelUsername->setBuddy(editUsername);
    labelUsername->setGeometry(uxPos-300, uyPos, 200, 35);
    scene->addWidget(labelUsername);
    labelPassword->setFont(font);
    labelPassword->setText(QString("Password"));
    labelPassword->setBuddy(editPassword);
    labelPassword->setGeometry(uxPos-300, pyPos, 200, 35);
    scene->addWidget(labelPassword);

    // create the confirm button
    Button* confirmButton = new Button(QString("Confirm"));
    double ixPos = width()/2 - confirmButton->boundingRect().width()/2*3;
    double iyPos = height()/10*6;
    confirmButton->setPos(ixPos,iyPos);
    connect(confirmButton, &Button::clicked, this, [this]{ sign_in(editUsername->text().toStdString(), editPassword->text().toStdString()); });
    scene->addItem(confirmButton);

    // create the back button
    Button* backButton = new Button(QString("Back"));
    double bxPos = width()/2 + backButton->boundingRect().width()/2;
    double byPos = height()/10*6;
    backButton->setPos(bxPos,byPos);
    connect(backButton, &Button::clicked, this, [this]{ displayMainMenu(); });
    scene->addItem(backButton);
}

void GameManager::signupMenu() {

    // Clear all
    scene->clear();

    // initialize the username combo box so that it is editable
    editUsername = new QLineEdit();
    editUsername->setEchoMode(QLineEdit::Normal);
    int uxPos = width()/2;
    int uyPos = height()/10*2;
    editUsername->setGeometry(uxPos, uyPos, 300, 35);
    scene->addWidget(editUsername);
    // initialize the password field so that it does not echo characters
    editPassword = new QLineEdit();
    editPassword->setEchoMode(QLineEdit::Password);
    int pyPos = height()/10*3;
    editPassword->setGeometry(uxPos, pyPos, 300, 35);
    scene->addWidget(editPassword);
    // initialize the password confirm field so that it does not echo characters
    editPasswordConfirm = new QLineEdit();
    editPasswordConfirm->setEchoMode(QLineEdit::Password);
    int pcyPos = height()/10*4;
    editPasswordConfirm->setGeometry(uxPos, pcyPos, 300, 35);
    scene->addWidget(editPasswordConfirm);

    // initialize the labels
    QFont font("MV Boli", 15, QFont::Bold);
    QLabel* labelUsername = new QLabel();
    QLabel* labelPassword = new QLabel();
    QLabel* labelPasswordConfirm = new QLabel();
    labelUsername->setFont(font);
    labelUsername->setText(QString("Username"));
    labelUsername->setBuddy(editUsername);
    labelUsername->setGeometry(uxPos-300, uyPos, 300, 35);
    scene->addWidget(labelUsername);
    labelPassword->setFont(font);
    labelPassword->setText(QString("Password"));
    labelPassword->setBuddy(editPassword);
    labelPassword->setGeometry(uxPos-300, pyPos, 300, 35);
    scene->addWidget(labelPassword);
    labelPasswordConfirm->setFont(font);
    labelPasswordConfirm->setText(QString("Password Confirm"));
    labelPasswordConfirm->setBuddy(editPassword);
    labelPasswordConfirm->setGeometry(uxPos-300, pcyPos, 300, 35);
    scene->addWidget(labelPasswordConfirm);

    // create the confirm button
    Button* confirmButton = new Button(QString("Confirm"));
    double ixPos = width()/2 - confirmButton->boundingRect().width()/2*3;
    double iyPos = height()/10*6;
    confirmButton->setPos(ixPos,iyPos);
    connect(confirmButton, &Button::clicked, this, [this]{ sign_up(editUsername->text().toStdString(), editPassword->text().toStdString(), editPasswordConfirm->text().toStdString()); });
    scene->addItem(confirmButton);

    // create the back button
    Button* backButton = new Button(QString("Back"));
    double bxPos = width()/2 + backButton->boundingRect().width()/2;
    double byPos = height()/10*6;
    backButton->setPos(bxPos,byPos);
    connect(backButton, &Button::clicked, this, [this]{ displayMainMenu(); });
    scene->addItem(backButton);
}

void GameManager::sign_in(const std::string& username, const std::string& password) {

    std::cout << username << "|" << password << std::endl;
    try {
        transport->open();

        if(client.sign_in(username, password)) {
            std::cout << "success sign in" << std::endl;
            start();
        }
        else {
            std::cout << "fail to sign in" << std::endl;
            QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString("fail to sign in"));
            double txPos = width()/2 - err_msg->boundingRect().width()/2;
            double tyPos = height()/5;
            err_msg->setPos(txPos,tyPos);
            signinMenu();
            scene->addItem(err_msg);
        }

    } catch (const InvalidOperation& io) {
        std::cout << io.err_code << ": " << io.why << std::endl;
        QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString::fromStdString(io.why));
        double txPos = width()/2 - err_msg->boundingRect().width()/2;
        double tyPos = height()/5;
        err_msg->setPos(txPos,tyPos);
        signinMenu();
        scene->addItem(err_msg);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    transport->close();
}

void GameManager::sign_up(const std::string& username, const std::string& password, const std::string& password_confirm) {

    std::cout << username << "|" << password << "|" << password_confirm << std::endl;
    if(password!=password_confirm) {
        QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString("password confirm not match"));
        double txPos = width()/2 - err_msg->boundingRect().width()/2;
        double tyPos = height()/5;
        err_msg->setPos(txPos,tyPos);
        signupMenu();
        scene->addItem(err_msg);
        return;
    }
    try {
        transport->open();

        if(client.sign_up(username, password)) {
            std::cout << "success sign up" << std::endl;
            start();
        }
        else {
            std::cout << "fail to sign up" << std::endl;
            QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString("fail to sign up"));
            double txPos = width()/2 - err_msg->boundingRect().width()/2;
            double tyPos = height()/5;
            err_msg->setPos(txPos,tyPos);
            signupMenu();
            scene->addItem(err_msg);
        }

    } catch (const InvalidOperation& io) {
        std::cout << io.err_code << ": " << io.why << std::endl;
        QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString::fromStdString(io.why));
        double txPos = width()/2 - err_msg->boundingRect().width()/2;
        double tyPos = height()/5;
        err_msg->setPos(txPos,tyPos);
        signupMenu();
        scene->addItem(err_msg);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    transport->close();
}

void GameManager::start() {

    // Clear all
    scene->clear();

    Card* c = new Card("BackBlue");
    c->setPos(190, 300);
    scene->addItem(c);

    Card* c2 = new Card("Spade2");
    c2->setPos(200, 300);
    scene->addItem(c2);

    Card* c3 = new Card("Heart5");
    c3->setPos(210, 300);
    scene->addItem(c3);
}
