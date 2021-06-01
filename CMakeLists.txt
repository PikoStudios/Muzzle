cmake_minimum_required(VERSION 3.18)

project(Muzzle)
INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(lib)

add_executable(main src/main.c)
TARGET_LINK_LIBRARIES(main glfw3 opengl32 gdi32)
