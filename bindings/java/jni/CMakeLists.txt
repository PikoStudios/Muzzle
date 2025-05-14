cmake_minimum_required(VERSION 3.18)

project(muzzlejni)
set(MUZZLE_ROOT "../../../")
set(MUZZLE_DEPS_FOLDER ${MUZZLE_ROOT}/deps)
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/lib)
set(MUZZLE_DEPS_FOLDER ${MUZZLE_ROOT}/deps)
set(FREETYPE ${MUZZLE_DEPS_FOLDER}/freetype)
set(target_name muzzlejni)

find_package(JNI REQUIRED)

include_directories(${MUZZLE_ROOT}/include ${FREETYPE}/include ${JNI_INCLUDE_DIRS})
link_directories(${MUZZLE_LIB_FOLDER} ${MUZZLE_DEPS_FOLDER}/glfw/lib ${FREETYPE}/lib_pic ${FREETYPE}/lib)

set(source
src/common.c
src/jni_applet.c
src/jni_circle.c
src/jni_drawing.c
src/jni_font.c
src/jni_input.c
src/jni_rectangle.c
src/jni_sprite.c
src/jni_text.c
src/jni_shader.c
src/jni_shader_buffer.c
src/jni_shader_pipeline.c
src/jni_sprite_batch.c
)

add_library(muzzlejni SHARED ${source})
target_link_libraries(muzzlejni muzzle ${JNI_LIBRARIES})

message(STATUS "Checking OS")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Checking OS - found (Darwin/MacOS)")
    message(WARNING "Checking OS - warning (Darwin/MacOS support in this CMakeLists.txt is very limited)")

    target_link_libraries(${target_name} muzzle ${JNI_LIBRARIES} glfw3 freetype CoreVideo OpenGL IOKit Cocoa Carbon)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Checking OS - found (WIN32)")
    target_link_libraries(${target_name} muzzle ${JNI_LIBRARIES} glfw3 freetype opengl32 gdi32 DSound)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Checking OS - found (Linux)")
    target_link_libraries(${target_name} muzzle ${JNI_LIBRARIES} glfw3 freetype GL m z)

else ()
# Default to Unix
    message(STATUS "Checking OS - not found (Unix)")
    target_link_libraries(${target_name} muzzle ${JNI_LIBRARIES} glfw3 freetype GL m z)
endif ()
