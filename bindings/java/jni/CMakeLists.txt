cmake_minimum_required(VERSION 3.18)

project(muzzlejni)
set(MUZZLE_ROOT "../../")
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/deps)

find_package(JNI REQUIRED)

include_directories(${MUZZLE_ROOT}/include ${MUZZLE_LIB_FOLDER}/freetype/include ${JNI_INCLUDE_DIRS})
link_directories(${MUZZLE_LIB_FOLDER}/glfw/lib ${MUZZLE_LIB_FOLDER}/freetype/lib)

set(source
src/common.c
src/jni_applet.c
src/jni_circle.c
src/jni_drawing.c
src/jni_font.c
src/jni_key.c
src/jni_mouse.c
src/jni_rectangle.c
src/jni_sprite.c
src/jni_text.c
)

add_library(muzzlejni SHARED ${source})
target_link_libraries(muzzlejni muzzle ${JNI_LIBRARIES})
