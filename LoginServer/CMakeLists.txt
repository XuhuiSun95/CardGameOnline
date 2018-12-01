cmake_minimum_required (VERSION 2.6)
set(target_name LoginServer)

set (CMAKE_CXX_STANDARD 11)

project (${target_name} C CXX)

include_directories(/usr/local/mysql/connector-c++-8.0/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
link_directories(/usr/local/mysql/connector-c++-8.0/lib64/debug)

add_executable(${target_name}
    src/main.cpp
    src/SystemManager.cpp
    src/ConfigLoader.cpp
    src/INIReader.cpp
    src/ini.c
    src/Database.cpp
    src/GameLobbyServer.cpp
    src/GameLobbyHandler.cpp
    src/GLS/GameLobby.cpp
    src/GLS/cgo_constants.cpp
    src/GLS/cgo_types.cpp
    )

target_link_libraries(${target_name}
    -lmysqlcppconn8
    -lthrift
    -lthriftnb
    -levent
    -lcryptopp
    )
