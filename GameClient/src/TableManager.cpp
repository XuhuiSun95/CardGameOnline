#include "TableManager.h"

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using boost::shared_ptr;

TableManager::TableManager(QGraphicsScene* ptr, const Game g, const int id, QGraphicsPixmapItem* parent) : QGraphicsRectItem (parent) {

    // Table id
    mScene = ptr;
    mGame = g;
    mId = id;

    // Base table rect
    setRect(0,0,100,100);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);
}

void TableManager::upate_slots(std::vector<bool> &slot) {

    QString aval;
    for(int i=0; i<slot.size(); i++) {
        aval = slot[i]? "Seated" : "Empty";
        Button* seat = new Button(aval, 50, 50);
        seat->setRect(0,0,50,50);
        int xPos, yPos;
        if(i==0) {
            xPos= x() + rect().width()/2 - seat->boundingRect().width()/2;
            yPos = y() - seat->boundingRect().height()/2 - 30;
        } else if(i==1) {
            xPos= x() + rect().width() - seat->boundingRect().width()/2 + 30;
            yPos = y() + rect().height()/2 - seat->boundingRect().height()/2;
        } else if(i==2) {
            xPos= x() + rect().width()/2 - seat->boundingRect().width()/2;
            yPos = y() + rect().height() - seat->boundingRect().height()/2 + 30;
        } else if(i==3) {
            xPos= x() - seat->boundingRect().width()/2 - 30;
            yPos = y() + rect().height()/2 - seat->boundingRect().height()/2;
        }
        seat->setPos(xPos,yPos);
        mScene->addItem(seat);
        connect(seat, &Button::clicked, this, [this,i]{ pick_slot(i); });
    }
}

void TableManager::pick_slot(int i) {

    std::cout << "table id = " << mId << std::endl;
    std::cout << "seat id = " << i << std::endl;

    // connect game server
    boost::shared_ptr<TTransport> g_socket(new TSocket(mGame.host, mGame.port));
    boost::shared_ptr<TTransport> g_transport(new TFramedTransport(g_socket));
    boost::shared_ptr<TProtocol> g_protocol(new TCompactProtocol(g_transport));
    CardGameClient g_client(g_protocol);

    // fetch table info
    try {
        g_transport->open();

        if(g_client.join_table(mId, i)) {
            std::cout << "success join table " << mId << " ,seat " << i << std::endl;
        }
        else {
            std::cout << "unable to join table " << mId << " ,seat " << i << std::endl;
        }
        g_transport->close();

    } catch (const std::exception& e) {
        g_transport->close();
        std::cout << e.what() << std::endl;
    }
}
