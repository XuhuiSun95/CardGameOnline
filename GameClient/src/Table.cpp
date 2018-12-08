#include "Table.h"

Table::Table(QGraphicsScene* ptr, const int id, QGraphicsPixmapItem* parent) : QGraphicsRectItem (parent) {

    // Table id
    mScene = ptr;
    mId = id;

    // Base table rect
    setRect(0,0,100,100);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    setBrush(brush);
}

void Table::upate_slot(std::vector<bool> &slot) {

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
        connect(seat, &Button::clicked, this, [this, i]{ (pick_slot(i)); });
    }
}

void Table::pick_slot(int i) {

    std::cout << "table id = " << mId << std::endl;
    std::cout << "seat id = " << i << std::endl;
}
