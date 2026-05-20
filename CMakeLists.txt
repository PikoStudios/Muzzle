cmake_minimum_required(VERSION 3.18)

project(Muzzle VERSION 3)
set(MUZZLE_ROOT ".")
set(MUZZLE_LIB_FOLDER ${MUZZLE_ROOT}/deps)
set(OPTIMIZATION_LEVEL 2)

include_directories(${MUZZLE_ROOT}/include ${MUZZLE_LIB_FOLDER}/freetype/include)
link_directories(${MUZZLE_LIB_FOLDER}/glfw/lib ${MUZZLE_LIB_FOLDER}/freetype/lib)
set(mz_source_dir ${MUZZLE_ROOT}/src)

#could use aux_source_directory() but its better to list each file to ensure new files are compiled
#https://stackoverflow.com/a/25077976/10415312

set(mz_internal_src
${mz_source_dir}/internals/file_helper.c
${mz_source_dir}/internals/gl_callbacks.c
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
${mz_source_dir}/core/text_renderer.c
${mz_source_dir}/core/font.c
${mz_source_dir}/core/shader.c
${mz_source_dir}/core/pipeline.c
)

set(mz_primitives_src
${mz_source_dir}/primitives/rectangle.c
${mz_source_dir}/primitives/sprite.c
${mz_source_dir}/primitives/circle.c
${mz_source_dir}/primitives/text.c
)

set(mz_input_src
${mz_source_dir}/input/key.c
${mz_source_dir}/input/mouse.c
${mz_source_dir}/input/input_manager.c
${mz_source_dir}/input/joystick.c
)

set(mz_utils_src
${mz_source_dir}/utils/sleep.c
)

set(mz_source
${mz_internal_src}
${mz_core_src}
${mz_primitives_src}
${mz_input_src}
${mz_utils_src}
${MUZZLE_LIB_FOLDER}/glad/src/glad.c
)

set(target_name muzzle)

if (BUILD_SHARED_LIBS MATCHES ON)
    add_library(${target_name} SHARED ${mz_source})
    add_library(${target_name}d SHARED ${mz_source})

    message(STATUS "Checking OS")

    if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        message(STATUS "Checking OS - found (Darwin/MacOS)")
        message(WARNING "Checking OS - warning (Darwin/MacOS support in this CMakeLists.txt is very limited)")

        set(LIBS glfw3 freetype CoreVideo OpenGL IOKit Cocoa Carbon)
    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        message(STATUS "Checking OS - found (WIN32)")
        set(LIBS glfw3 freetype opengl32 gdi32 DSound)

    elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
        message(STATUS "Checking OS - found (Linux)")
        set(LIBS glfw3 freetype GL m z)

    else ()
    # Default to Unix
        message(STATUS "Checking OS - not found (Unix)")
        set(LIBS glfw3 freetype GL m z)
    endif ()

    target_link_libraries(${target_name} PUBLIC ${LIBS})
    target_link_libraries(${target_name}d PUBLIC ${LIBS})
else()
    add_library(${target_name} STATIC ${mz_source})
    add_library(${target_name}d STATIC ${mz_source})
endif()

set_target_properties(${target_name} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${target_name}d PROPERTIES VERSION ${PROJECT_VERSION})

target_compile_definitions(${target_name}d PRIVATE MUZZLE_DEBUG_BUILD)
target_compile_options(${target_name}d PRIVATE -g)
target_compile_options(${target_name} PRIVATE -O${OPTIMIZATION_LEVEL})
