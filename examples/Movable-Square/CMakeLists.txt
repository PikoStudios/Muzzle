cmake_minimum_required(VERSION 3.18)

project(Muzzle)
INCLUDE_DIRECTORIES(../../include)
LINK_DIRECTORIES(../../deps/glfw/lib)
set(mz_source_dir "../../src")

#could use aux_source_directory() but its better to list each file to ensure new files are compiled
#https://stackoverflow.com/a/25077976/10415312


set(mz_source
${mz_source_dir}/Applet.c
${mz_source_dir}/callback.c
${mz_source_dir}/Drawing.c
${mz_source_dir}/Error.c
${mz_source_dir}/Loop.c
${mz_source_dir}/Muzzle.c
${mz_source_dir}/Rectangle.c
${mz_source_dir}/tint.c
${mz_source_dir}/Circle.c
${mz_source_dir}/Input.c
${mz_source_dir}/Sprite.c
${mz_source_dir}/Text.c
)


add_executable(main src/main.c ${mz_source})
TARGET_LINK_LIBRARIES(main glfw3 opengl32 gdi32)