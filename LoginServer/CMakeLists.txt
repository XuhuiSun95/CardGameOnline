cmake_minimum_required (VERSION 2.6)
set(target_name LoginServer)

set (CMAKE_CXX_STANDARD 11)

project (${target_name} C CXX)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(${target_name}
               src/main.cpp
               src/SystemManager.cpp
               src/ConfigLoader.cpp
               src/INIReader.cpp
               src/ini.c
               src/Database.cpp
               #src/ThailandServer.cpp
               #src/ThailandServiceHandler.cpp
               #src/TS/ThailandService.cpp
               #src/TS/Thailand_constants.cpp
               #src/TS/Thailand_types.cpp
)

target_link_libraries(${target_name}
                      -lmysqlcppconn8
    #-lpthread
    #-lthrift
    #                   -lthriftnb
    #                   -levent
                      )