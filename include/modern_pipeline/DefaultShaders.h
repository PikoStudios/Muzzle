// Default GLSL Shaders
#pragma once

#ifndef MZ_DEFAULT_VERTEX_SHADER
    #define MZ_DEFAULT_VERTEX_SHADER "#version 330 core\n" \
    "layout (location=0) in vec3 aPos;\n" \
    "layout (location=1) in vec4 aColor;\n" \
    "out vec4 fColor;\n" \
    "void main()\n" \
    "{\n" \
    "fColor = aColor;\n" \
    "gl_Position = vec4(aPos, 1.0);\n" \
    "}\n\0"
#endif

#ifndef MZ_DEFAULT_FRAGMENT_SHADER
    #define MZ_DEFAULT_FRAGMENT_SHADER "#version 330 core\n" \
    "in vec4 fColor;\n" \
    "out vec4 color;\n" \
    "void main()\n" \
    "{\n" \
    "color= fColor;\n" \
    "}\n"
#endif