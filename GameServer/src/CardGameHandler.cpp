#include "CardGameHandler.h"

CardGameHandler::CardGameHandler(const Config& cfg) {

    mConfig = &cfg;

    Table t;
    for(int i=0; i<mConfig->slot_size; i++) {
        t.slot.push_back(false);
    }
    for(int i=0; i<mConfig->table_size; i++) {
        t.table_id = i;
        mTables.push_back(t);
    }
}

void CardGameHandler::fetch_tables(std::vector<Table>& _return) {

    std::lock_guard<std::mutex> lock(tbl_mtx);
    _return = mTables;
}

bool CardGameHandler::join_table(const int32_t table_id, const int32_t slot_id) {
    
    std::cout << "join table: [" << table_id << "][" << slot_id << "]" << std::endl;
    std::lock_guard<std::mutex> lock(tbl_mtx);
    if(!mTables[table_id].slot[slot_id]) {
        mTables[table_id].slot[slot_id] = true;
        std::cout << "join table end" << std::endl;
        return true;
    }
    std::cout << "join table end" << std::endl;
    return false;
}

void CardGameHandler::ready_confirm(const bool ready) {
}

void CardGameHandler::play_card(TRM_OBJ& _return, const Method::type m, const TRM_OBJ& obj) {
}
