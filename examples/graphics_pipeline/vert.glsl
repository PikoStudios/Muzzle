#version 450

#define Z_NEAR 0.5
#define Z_FAR 500
#define CAMERA_ANGLE radians(0.0)

#define ROTATION_MATRIX mat4(\
	right.x, 0.0, -forward.x, 0.0,\
	right.y, 1.0, -forward.y, 0.0,\
	right.z, 0.0, -forward.z, 0.0,\
	0.0, 0.0, 0.0, 1.0\
)

#define TRANSLATION_MATRIX mat4(\
	1.0, 0.0, 0.0, 0.0,\
	0.0, 1.0, 0.0, 0.0,\
	0.0, 0.0, 1.0, 0.0,\
	-cameraPosition.x, -cameraPosition.y, -cameraPosition.z, 1.0\
)

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;

layout (location = 0) out vec4 vColor;

uniform vec2 uScreenResolution;
uniform float uCameraFov;
uniform float uTime;

const vec3 up = vec3(0.0, 1.0, 0.0);
const vec3 cameraPosition = vec3(0.0,0.0,3.0);
const vec3 forward = normalize(vec3(sin(CAMERA_ANGLE), 0.0, -cos(CAMERA_ANGLE)));
const vec3 right = normalize(cross(forward, up));

const mat4 view = ROTATION_MATRIX * TRANSLATION_MATRIX;

mat4 rotation()
{
	float angle = uTime * 0.7;

	float c = cos(angle);
	float s = sin(angle);

	mat4 xRotation = mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, c, -s, 0.0,
		0.0, s, c, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	mat4 yRotation = mat4(
		c, 0.0, -s, 0.0,
		0.0, 1.0, 0.0, 0.0,
		s, 0.0, c, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	return yRotation * xRotation;
}

mat4 viewPerspective()
{
	float aspect = uScreenResolution.x / uScreenResolution.y;
	float fov = radians(uCameraFov);
	float fov_y = 2 * atan(tan(fov/2)/aspect);
	float f = 1.0 / tan(fov_y / 2);

	mat4 perspective = mat4(
		f/aspect, 0.0, 0.0, 0.0,
		0.0, f, 0.0, 0.0,
		0.0, 0.0, -(Z_FAR+Z_NEAR)/(Z_FAR-Z_NEAR), -1.0,
		0.0, 0.0, -(2*Z_FAR*Z_NEAR)/(Z_FAR-Z_NEAR), 0.0
	);

	return perspective * view;
}

void main()
{
	vColor = aColor;
	gl_Position = viewPerspective() * rotation() * vec4(aPosition, 1.0);
}
