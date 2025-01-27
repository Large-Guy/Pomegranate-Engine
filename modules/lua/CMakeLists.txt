set(POMEGRANATE_LUA_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/lua_state.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/lua_state.h
        ${CMAKE_CURRENT_SOURCE_DIR}/debug.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/debug.h
        ${CMAKE_CURRENT_SOURCE_DIR}/events.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/events.h
        ${CMAKE_CURRENT_SOURCE_DIR}/ecs.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ecs.h
)

set(POMEGRANATE_LUA_INCLUDE_DIRS
        ../
)

add_library(PomegranateLua ${POMEGRANATE_LUA_SOURCES})

target_include_directories(PomegranateLua PUBLIC ${POMEGRANATE_LUA_INCLUDE_DIRS})

target_link_libraries(PomegranateLua PomegranateCore PomegranateEvents PomegranateECS)

# LuaJIT installer
if (APPLE)
    execute_process(
            COMMAND sh ./install/luajit_mac.sh
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(PomegranateLua ${CMAKE_CURRENT_SOURCE_DIR}/external/LuaJIT/src/libluajit.a)

elseif (UNIX)
    execute_process(
            COMMAND sh ./install/luajit_linux.sh
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )

    target_link_libraries(PomegranateLua ${CMAKE_CURRENT_SOURCE_DIR}/external/LuaJIT/src/libluajit.a)
elseif (WIN32)
    message(FATAL_ERROR "Windows is not supported yet")
endif ()