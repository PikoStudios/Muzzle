#version 450
#define MAX_ITERATIONS 100.0

layout (location = 0) in vec2 vTexCoord;
layout (location = 0) out vec4 fFragColor;

uniform vec2 uScreenResolution;
uniform float uDepth;

vec2 complexSquare(vec2 n)
{
    return vec2(
        pow(n.x, 2.) - pow(n.y, 2.),
        2. * n.x * n.y
    );
}

float iterate(vec2 coord)
{
    vec2 z = vec2(0);

    for (int i = 0; i < int(MAX_ITERATIONS); i++)
    {
        z = complexSquare(z) + coord * uDepth;

        if (length(z) > 2.)
        {
            return float(i) / MAX_ITERATIONS;
        }
    }

    return MAX_ITERATIONS;
}

void main()
{
    vec2 uv = (gl_FragCoord.xy - 0.5 * uScreenResolution.xy) / uScreenResolution.y;
    fFragColor = vec4(vec3(0.0) + iterate(uv), 1.0);
}
