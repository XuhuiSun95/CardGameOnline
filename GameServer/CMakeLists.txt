cmake_minimum_required (VERSION 2.6)
set(target_name GameServer)

set (CMAKE_CXX_STANDARD 11)

project (${target_name} C CXX)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(${target_name}
    src/main.cpp
    src/SystemManager.cpp
    src/ConfigLoader.cpp
    src/INIReader.cpp
    src/ini.c
    src/CardGameServer.cpp
    src/CardGameHandler.cpp
    src/CGS/CardGame.cpp
    src/CGS/cg_constants.cpp
    src/CGS/cg_types.cpp
    src/GLS/GameLobby.cpp
    src/GLS/cgo_constants.cpp
    src/GLS/cgo_types.cpp
    )

target_link_libraries(${target_name}
    -lthrift
    -lthriftnb
    -levent
    )
