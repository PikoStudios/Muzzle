#include "core/Error.h"

void muzzle_error(int error, const char *desc) 
{
    fprintf(stderr, "%s", desc);
}
void log_status(StatusTypes type, const char *status)
{
    switch (type)
    {
    case FATAL_ERROR:
        fprintf(stderr, "\e[0;31m\e[4;31m[FATAL] :: %s", status);
        exit(-1);
        break;
    case WARNING:
        printf("\e[0;33m\e[4;33m[WARNING] :: %s", status);
        break;

    case ERROR:
        fprintf(stderr, "\e[0;31m\e[4;31m[ERROR] :: %s", status);
        break;

    case SUCCESS:
        printf("\e[0;32m\e[4;32m[SUCCESS] :: %s", status);
        break;

    case INFO:
        printf("\e[0;34m\e[4;34m[INFO] :: %s", status);
        break;

    default:
        break;
    }
    
}
