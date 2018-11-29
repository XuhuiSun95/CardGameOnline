enum Game {
    DOUDIZHU = 1,
}

struct Path {
    1: string host,
    2: i32 port
}

# ==============================================
# err_code:
# 0xx series: system error
#     1: system busy
# 1xx series: sign up error
#     101: username exist
# 2xx series: sign in error
#     201: username/password not match or exist
# =============================================
exception InvalidOperation {
    1: i32 err_code,
    2: string why
}

service GameLobby {

    bool sign_up(1:string username, 2:string password) throws (1:InvalidOperation e),

    bool sign_in(1:string username, 2:string password) throws (1:InvalidOperation e),

    Path fetch_game(1:Game g)
}
