cmake_minimum_required(VERSION 3.18)

project(Muzzle)
INCLUDE_DIRECTORIES(../../include)
LINK_DIRECTORIES(../../deps/glfw/lib)

#could use aux_source_directory() but its better to list each file to ensure new files are compiled
#https://stackoverflow.com/a/25077976/10415312
add_executable(main main.c ../../src/Applet.c ../../src/callback.c ../../src/Drawing.c ../../src/Error.c ../../src/Loop.c ../../src/Muzzle.c ../../src/Rectangle.c ../../src/tint.c ../../src/Circle.c ../../src/Input.c)
TARGET_LINK_LIBRARIES(main glfw3 opengl32 gdi32)