#include "Menu.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::shared_ptr;

Menu::Menu(QGraphicsScene *ptr, QWidget* parent) :
    socket(new TSocket("localhost", 9001)),
    transport(new TFramedTransport(socket)),
    protocol(new TCompactProtocol(transport)),
    client(protocol) {

    mScene = ptr;
    mParent = parent;
    mLobby = new LobbyManager(mScene, transport, &client);
}

void Menu::display_main_menu() {

    // Clear all
    mScene->clear();

    // Menu title
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Card Game Online"));
    QFont titleFont("comic sans", 50);
    titleText->setFont(titleFont);
    double txPos = mScene->width()/2 - titleText->boundingRect().width()/2;
    double tyPos = mScene->height()/5;
    titleText->setPos(txPos,tyPos);
    mScene->addItem(titleText);

    // create the sign_in button
    Button* signinButton = new Button(QString("Sign in"),200,50);
    double ixPos = mScene->width()/2 - signinButton->boundingRect().width()/2;
    double iyPos = mScene->height()/10*5;
    signinButton->setPos(ixPos,iyPos);
    connect(signinButton, &Button::clicked, this, [this]{ signin_menu(); });
    mScene->addItem(signinButton);

    // create the sign_up button
    Button* signupButton = new Button(QString("Sign up"),200,50);
    double uxPos = mScene->width()/2 - signupButton->boundingRect().width()/2;
    double uyPos = mScene->height()/10*6;
    signupButton->setPos(uxPos,uyPos);
    connect(signupButton, &Button::clicked, this, [this]{ signup_menu(); });
    mScene->addItem(signupButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"),200,50);
    double qxPos = mScene->width()/2 - quitButton->boundingRect().width()/2;
    double qyPos = mScene->height()/10*7;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, &Button::clicked, this, [this]{ mParent->close(); });
    mScene->addItem(quitButton);
}

void Menu::signin_menu() {

    // Clear all
    mScene->clear();

    // initialize the username combo box so that it is editable
    editUsername = new QLineEdit();
    editUsername->setEchoMode(QLineEdit::Normal);
    int uxPos = mScene->width()/2;
    int uyPos = mScene->height()/10*3;
    editUsername->setGeometry(uxPos, uyPos, 300, 35);
    mScene->addWidget(editUsername);
    // initialize the password field so that it does not echo characters
    editPassword = new QLineEdit();
    editPassword->setEchoMode(QLineEdit::Password);
    int pyPos = mScene->height()/10*4;
    editPassword->setGeometry(uxPos, pyPos, 300, 35);
    mScene->addWidget(editPassword);

    // initialize the labels
    QFont font("MV Boli", 15, QFont::Bold);
    QLabel* labelUsername = new QLabel();
    QLabel* labelPassword = new QLabel();
    labelUsername->setFont(font);
    labelUsername->setText(QString("Username"));
    labelUsername->setBuddy(editUsername);
    labelUsername->setGeometry(uxPos-300, uyPos, 200, 35);
    mScene->addWidget(labelUsername);
    labelPassword->setFont(font);
    labelPassword->setText(QString("Password"));
    labelPassword->setBuddy(editPassword);
    labelPassword->setGeometry(uxPos-300, pyPos, 200, 35);
    mScene->addWidget(labelPassword);

    // create the confirm button
    Button* confirmButton = new Button(QString("Confirm"),200,50);
    double ixPos = mScene->width()/2 - confirmButton->boundingRect().width()/2*3;
    double iyPos = mScene->height()/10*6;
    confirmButton->setPos(ixPos,iyPos);
    connect(confirmButton, &Button::clicked, this, [this]{ sign_in(editUsername->text().toStdString(), editPassword->text().toStdString()); });
    mScene->addItem(confirmButton);

    // create the back button
    Button* backButton = new Button(QString("Back"),200,50);
    double bxPos = mScene->width()/2 + backButton->boundingRect().width()/2;
    double byPos = mScene->height()/10*6;
    backButton->setPos(bxPos,byPos);
    connect(backButton, &Button::clicked, this, [this]{ display_main_menu(); });
    mScene->addItem(backButton);
}

void Menu::signup_menu() {

    // Clear all
    mScene->clear();

    // initialize the username combo box so that it is editable
    editUsername = new QLineEdit();
    editUsername->setEchoMode(QLineEdit::Normal);
    int uxPos = mScene->width()/2;
    int uyPos = mScene->height()/10*2;
    editUsername->setGeometry(uxPos, uyPos, 300, 35);
    mScene->addWidget(editUsername);
    // initialize the password field so that it does not echo characters
    editPassword = new QLineEdit();
    editPassword->setEchoMode(QLineEdit::Password);
    int pyPos = mScene->height()/10*3;
    editPassword->setGeometry(uxPos, pyPos, 300, 35);
    mScene->addWidget(editPassword);
    // initialize the password confirm field so that it does not echo characters
    editPasswordConfirm = new QLineEdit();
    editPasswordConfirm->setEchoMode(QLineEdit::Password);
    int pcyPos = mScene->height()/10*4;
    editPasswordConfirm->setGeometry(uxPos, pcyPos, 300, 35);
    mScene->addWidget(editPasswordConfirm);

    // initialize the labels
    QFont font("MV Boli", 15, QFont::Bold);
    QLabel* labelUsername = new QLabel();
    QLabel* labelPassword = new QLabel();
    QLabel* labelPasswordConfirm = new QLabel();
    labelUsername->setFont(font);
    labelUsername->setText(QString("Username"));
    labelUsername->setBuddy(editUsername);
    labelUsername->setGeometry(uxPos-300, uyPos, 300, 35);
    mScene->addWidget(labelUsername);
    labelPassword->setFont(font);
    labelPassword->setText(QString("Password"));
    labelPassword->setBuddy(editPassword);
    labelPassword->setGeometry(uxPos-300, pyPos, 300, 35);
    mScene->addWidget(labelPassword);
    labelPasswordConfirm->setFont(font);
    labelPasswordConfirm->setText(QString("Password Confirm"));
    labelPasswordConfirm->setBuddy(editPassword);
    labelPasswordConfirm->setGeometry(uxPos-300, pcyPos, 300, 35);
    mScene->addWidget(labelPasswordConfirm);

    // create the confirm button
    Button* confirmButton = new Button(QString("Confirm"),200,50);
    double ixPos = mScene->width()/2 - confirmButton->boundingRect().width()/2*3;
    double iyPos = mScene->height()/10*6;
    confirmButton->setPos(ixPos,iyPos);
    connect(confirmButton, &Button::clicked, this, [this]{ sign_up(editUsername->text().toStdString(), editPassword->text().toStdString(), editPasswordConfirm->text().toStdString()); });
    mScene->addItem(confirmButton);

    // create the back button
    Button* backButton = new Button(QString("Back"),200,50);
    double bxPos = mScene->width()/2 + backButton->boundingRect().width()/2;
    double byPos = mScene->height()/10*6;
    backButton->setPos(bxPos,byPos);
    connect(backButton, &Button::clicked, this, [this]{ display_main_menu(); });
    mScene->addItem(backButton);
}

void Menu::sign_in(const std::string& username, const std::string& password) {

    std::cout << username << "|" << password << std::endl;
    try {
        transport->open();

        if(client.sign_in(username, password)) {
            std::cout << "success sign in" << std::endl;
            mLobby->display_lobby_menu();
        }
        else {
            std::cout << "fail to sign in" << std::endl;
            QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString("fail to sign in"));
            double txPos = mScene->width()/2 - err_msg->boundingRect().width()/2;
            double tyPos = mScene->height()/7;
            err_msg->setPos(txPos,tyPos);
            signin_menu();
            mScene->addItem(err_msg);
        }
        transport->close();

    } catch (const InvalidOperation& io) {
        transport->close();
        std::cout << io.err_code << ": " << io.why << std::endl;
        QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString::fromStdString(io.why));
        double txPos = mScene->width()/2 - err_msg->boundingRect().width()/2;
        double tyPos = mScene->height()/7;
        err_msg->setPos(txPos,tyPos);
        signin_menu();
        mScene->addItem(err_msg);
    } catch (const std::exception& e) {
        transport->close();
        std::cout << e.what() << std::endl;
    }
}

void Menu::sign_up(const std::string& username, const std::string& password, const std::string& password_confirm) {

    std::cout << username << "|" << password << "|" << password_confirm << std::endl;
    if(password!=password_confirm) {
        QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString("password confirm not match"));
        double txPos = mScene->width()/2 - err_msg->boundingRect().width()/2;
        double tyPos = mScene->height()/7;
        err_msg->setPos(txPos,tyPos);
        signup_menu();
        mScene->addItem(err_msg);
        return;

    }
    try {
        transport->open();

        if(client.sign_up(username, password)) {
            std::cout << "success sign up" << std::endl;
            mLobby->display_lobby_menu();
        }
        else {
            std::cout << "fail to sign up" << std::endl;
            QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString("fail to sign up"));
            double txPos = mScene->width()/2 - err_msg->boundingRect().width()/2;
            double tyPos = mScene->height()/7;
            err_msg->setPos(txPos,tyPos);
            signup_menu();
            mScene->addItem(err_msg);
        }
        transport->close();

    } catch (const InvalidOperation& io) {
        transport->close();
        std::cout << io.err_code << ": " << io.why << std::endl;
        QGraphicsTextItem* err_msg = new QGraphicsTextItem(QString::fromStdString(io.why));
        double txPos = mScene->width()/2 - err_msg->boundingRect().width()/2;
        double tyPos = mScene->height()/7;
        err_msg->setPos(txPos,tyPos);
        signup_menu();
        mScene->addItem(err_msg);
    } catch (const std::exception& e) {
        transport->close();
        std::cout << e.what() << std::endl;
    }
}
