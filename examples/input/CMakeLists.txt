cmake_minimum_required(VERSION 3.18)

project(Muzzle)
INCLUDE_DIRECTORIES(../../include)
LINK_DIRECTORIES(../../deps/glfw/lib)

add_executable(main main.c ../../src/Applet.c ../../src/callback.c ../../src/Drawing.c ../../src/Error.c ../../src/Loop.c ../../src/Muzzle.c ../../src/Rectangle.c ../../src/tint.c ../../src/Circle.c ../../src/Input.c)
TARGET_LINK_LIBRARIES(main glfw3 opengl32 gdi32)
