cmake_minimum_required(VERSION 3.15)
project(flappy-bird LANGUAGES C CXX)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/game.h
        src/game.cpp
        src/bird.h
        src/bird.cpp
        src/pipe.h
        src/pipe.cpp
)

target_link_libraries(${PROJECT_NAME} raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()
