cmake_minimum_required(VERSION 3.18)

project(Muzzle VERSION 3)
set(MUZZLE_ROOT "../..")
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/deps)

set(CMAKE_BUILD_TYPE Debug)

INCLUDE_DIRECTORIES(${MUZZLE_ROOT}/include ${MUZZLE_LIB_FOLDER}/freetype/include)
LINK_DIRECTORIES(${MUZZLE_LIB_FOLDER}/glfw/lib ${MUZZLE_LIB_FOLDER}/freetype/lib)
set(mz_source_dir ${MUZZLE_ROOT}/src)

#could use aux_source_directory() but its better to list each file to ensure new files are compiled
#https://stackoverflow.com/a/25077976/10415312

set(mz_internal_src
${mz_source_dir}/internals/file_helper.c
${mz_source_dir}/internals/glfw_callbacks.c
${mz_source_dir}/internals/glfw_error_helper.c
${mz_source_dir}/internals/quad_indices.c
)

set(mz_core_src
${mz_source_dir}/core/applet.c
${mz_source_dir}/core/drawing.c
${mz_source_dir}/core/logging.c
${mz_source_dir}/core/memory.c
${mz_source_dir}/core/quad_renderer.c
${mz_source_dir}/core/sprite_renderer.c
${mz_source_dir}/core/circle_renderer.c
${mz_source_dir}/core/shader.c
)

set(mz_primitives_src
${mz_source_dir}/primitives/rectangle.c
${mz_source_dir}/primitives/sprite.c
${mz_source_dir}/primitives/circle.c
)

set(mz_input_src
${mz_source_dir}/input/key.c
${mz_source_dir}/input/mouse.c
)

set(mz_source
${mz_internal_src}
${mz_core_src}
${mz_primitives_src}
${mz_input_src}
${MUZZLE_LIB_FOLDER}/glad/src/glad.c
)

if (BUILD_SHARED_LIBS MATCHES ON)
    add_library(muzzle ${mz_source})
    set_target_properties(muzzle PROPERTIES VERSION ${PROJECT_VERSION})
    set(target_name muzzle)
else()
    add_executable(main main.c ${mz_source})
    set(target_name main)
endif()

message(STATUS "Checking OS")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message(STATUS "Checking OS - found (Darwin/MacOS)")
    message(WARNING "Checking OS - warning (Darwin/MacOS support in this CMakeLists.txt is very limited)")
    
    TARGET_LINK_LIBRARIES(${target_name} glfw freetype CoreVideo OpenGL IOKit Cocoa Carbon)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message(STATUS "Checking OS - found (WIN32)")
    TARGET_LINK_LIBRARIES(${target_name} glfw3 freetype opengl32 gdi32 DSound)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(STATUS "Checking OS - found (Linux)")
    TARGET_LINK_LIBRARIES(${target_name} glfw freetype GL m)

else ()
# Default to Unix
    message(STATUS "Checking OS - not found (Unix)")
    TARGET_LINK_LIBRARIES(${target_name} glfw freetype GL m)
endif ()
