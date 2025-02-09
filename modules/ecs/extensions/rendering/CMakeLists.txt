set(POMEGRANATE_ECS_EXTENSIONS_RENDERING_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/rendering.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/rendering.h
        ${CMAKE_CURRENT_SOURCE_DIR}/mesh_instance.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/mesh_instance.h
        ${CMAKE_CURRENT_SOURCE_DIR}/camera3d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/camera3d.h
        ${CMAKE_CURRENT_SOURCE_DIR}/camera2d.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/camera2d.h
        ${CMAKE_CURRENT_SOURCE_DIR}/sprite.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sprite.h
)

add_library(PomegranateECSExtensionsRendering ${POMEGRANATE_ECS_EXTENSIONS_RENDERING_SOURCES})

target_include_directories(PomegranateECSExtensionsRendering PUBLIC
        ${POMEGRANATE_ECS_EXTENSIONS_RENDERING_INCLUDE_DIRS}
        ${POMEGRANATE_CORE_INCLUDE_DIRS}
        ${POMEGRANATE_GRAPHICS_INCLUDE_DIRS}
        ${POMEGRANATE_ECS_INCLUDE_DIRS}
        ${POMEGRANATE_MATH_INCLUDE_DIRS}
        ${POMEGRANATE_ECS_EXTENSIONS_COMMON_INCLUDE_DIRS})

target_link_libraries(PomegranateECSExtensionsRendering PomegranateCore PomegranateGraphics PomegranateECS PomegranateMath PomegranateECSExtensionsCommon)