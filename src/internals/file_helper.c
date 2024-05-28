#include "internals/file_helper.h"
#include "core/logging.h"
#include <stdio.h>

char* internals_read_file(FILE** file, const char* filepath, const char* msg_on_file_error, const char* msg_on_malloc_error)
{
	fopen_s(file, filepath, "r");

	if (file == NULL)
	{
		// TODO: give reason
		mz_log_status(LOG_STATUS_FATAL_ERROR, msg_on_file_error);
	}

	fseek(*file, 0, SEEK_END);
	const long int size = ftell(*file);
	fseek(*file, 0, SEEK_SET);

	char* buffer = MZ_MALLOC(sizeof(char) * (size + 1));

	if (buffer == NULL)
	{
		// TODO: Give reason
		fclose(*file);
		mz_log_status(LOG_STATUS_FATAL_ERROR, msg_on_malloc_error);
	}

	fread(buffer, size, 1, *file);
	buffer[size] = '\0';
	fclose(*file);

	return buffer;
}
