cmake_minimum_required(VERSION 3.15...4.00)
project(samurai-sword
        VERSION 0.0.1
        DESCRIPTION "badass process killer for Windows"
        LANGUAGES C)
set(SRC ${PROJECT_SOURCE_DIR}/src/main)
set(HDRS ${PROJECT_SOURCE_DIR}/src/include)
add_executable(ss 
                ${SRC}/pilot.c
                ${SRC}/ii.c)
target_include_directories(ss PRIVATE ${HDRS})