cmake_minimum_required(VERSION 3.5)
project(PomegranateEngine)

add_compile_options(-Wreturn-type)
add_compile_options(-Wuninitialized)
add_definitions(-DPOMEGRANATE_GRAPHICS_VULKAN_VALIDATION_LAYERS)
add_definitions(-DPOMEGRANATE_FUNCTION_VALIDATION_LAYERS)

# Enable MVK_CONFIG_USE_METAL_ARGUMENT_BUFFERS
add_compile_options(-DMVK_CONFIG_USE_METAL_ARGUMENT_BUFFERS=1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the modules

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/core)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/math)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/math/geometry)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/ecs)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/gameobjects)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/ecs/extensions/common)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/ecs/extensions/rendering)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/lua)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/events)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/graphics/opengl)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/audio)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/input)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/modules/plugins)

set(SOURCE_FILES
        ${SOURCE_DIR}/main.cpp
)

# Set include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/modules)

# Set the executable
add_executable(PomegranateEngine ${SOURCE_FILES})

# Link the modules
target_link_libraries(PomegranateEngine PomegranateCore)
target_link_libraries(PomegranateEngine PomegranateMath)
target_link_libraries(PomegranateEngine PomegranateMathGeometry)
target_link_libraries(PomegranateEngine PomegranateECS)
target_link_libraries(PomegranateEngine PomegranateGameObjects)
#target_link_libraries(PomegranateEngine PomegranateECSExtensionsCommon)
#target_link_libraries(PomegranateEngine PomegranateECSExtensionsRendering)
#target_link_libraries(PomegranateEngine PomegranateLua)
target_link_libraries(PomegranateEngine PomegranateEvents)
target_link_libraries(PomegranateEngine PomegranateGraphics)
#target_link_libraries(PomegranateEngine PomegranateAudio)
target_link_libraries(PomegranateEngine PomegranateInput)
target_link_libraries(PomegranateEngine PomegranatePlugin)


# Set the output directory for the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
