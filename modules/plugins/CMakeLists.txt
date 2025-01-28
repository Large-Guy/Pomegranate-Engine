set(POMEGRANATE_PLUGIN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/plugin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/plugin.h
)

set(POMEGRANATE_PLUGIN_INCLUDE_DIRS
        ../
)

add_library(PomegranatePlugin ${POMEGRANATE_PLUGIN_SOURCES})

target_include_directories(PomegranatePlugin PUBLIC ${POMEGRANATE_PLUGIN_INCLUDE_DIRS})

target_link_libraries(PomegranatePlugin PomegranateCore)