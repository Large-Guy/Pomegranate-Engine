cmake_minimum_required(VERSION 3.5)
project(TestPlugin)

set(POMEGRANATE_PLUGIN_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/plugin.cpp
)

# Output dynamic library
add_library(TestPlugin SHARED ${POMEGRANATE_PLUGIN_SOURCES})

# output it next to the executable
set_target_properties(TestPlugin PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)