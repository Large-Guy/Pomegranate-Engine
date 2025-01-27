set(POMEGRANATE_GAMEOBJECTS_SOURCES
        gameobject.cpp
        gameobject.h
        component.h
        component.cpp
)

set(POMEGRANATE_GAMEOBJECTS_INCLUDE_DIRS
        ../
)

add_library(PomegranateGameObjects ${POMEGRANATE_GAMEOBJECTS_SOURCES})

target_include_directories(PomegranateGameObjects PUBLIC ${POMEGRANATE_GAMEOBJECTS_INCLUDE_DIRS})

target_link_libraries(PomegranateGameObjects PomegranateCore)