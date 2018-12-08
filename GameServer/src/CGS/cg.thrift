struct Table {
    1: i32 table_id,
    2: list<bool> slot
}

struct Card {
    1: string type,
    2: string value
}

struct TRM_OBJ {
    1: i32 player_id,
    2: list<Card> played_cards
}

enum Method {
    GET = 1,
    POST = 2
}

service CardGame {

    list<Table> fetch_tables(),

    bool join_table(1:i32 table_id, 2:i32 slot_id),

    void ready_confirm(1:bool ready),

    TRM_OBJ play_card(1:Method m, 2:TRM_OBJ obj)
}
