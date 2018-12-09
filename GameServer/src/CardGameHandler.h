#ifndef CARDGAMEEHANDLER_H
#define CARDGAMEEHANDLER_H

#include <mutex>
#include "CGS/CardGame.h"
#include "ConfigLoader.h"


class CardGameHandler : virtual public CardGameIf {

public:
    
    CardGameHandler(const Config& cfg);

private:

    // private variable
    const Config* mConfig;
    std::mutex tbl_mtx;
    std::vector<Table> mTables;

    // handler
    void fetch_tables(std::vector<Table>& _return);
    bool join_table(const int32_t table_id, const int32_t slot_id);
    void ready_confirm(const bool ready);
    void play_card(TRM_OBJ& _return, const Method::type m, const TRM_OBJ& obj);

};

#endif
