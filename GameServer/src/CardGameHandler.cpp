#include "CardGameHandler.h"

CardGameHandler::CardGameHandler(const Config& cfg) {

    mConfig = &cfg;
}

void CardGameHandler::fetch_tables(std::vector<Table>& _return) {
}

bool CardGameHandler::join_table(const int32_t table_id, const int32_t slot_id) {
    
    return true;
}

void CardGameHandler::ready_confirm(const bool ready) {
}

void CardGameHandler::play_card(TRM_OBJ& _return, const Method::type m, const TRM_OBJ& obj) {
}
