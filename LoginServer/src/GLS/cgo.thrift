struct Game {
    1: string name,
    2: string host,
    3: i32 port
}

# ==============================================
# err_code:
# 0xx series: system error
#     1: system busy
# 1xx series: sign up error
#     101: username exist
#     102: username/password empty
# 2xx series: sign in error
#     201: username not exist
#     202: username/password not match
#     203: username/password empty
# =============================================
exception InvalidOperation {
    1: i32 err_code,
    2: string why
}

service GameLobby {

    bool sign_up(1:string username, 2:string password) throws (1:InvalidOperation e),

    bool sign_in(1:string username, 2:string password) throws (1:InvalidOperation e),

    void add_game(1:Game g),

    list<Game> fetch_games()
}
