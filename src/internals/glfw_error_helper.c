#include "internals/glfw_error_helper.h"

const char* internals_get_error_description(void)
{
	const char* buffer;
	glfwGetError(&buffer);

	return buffer;
}
