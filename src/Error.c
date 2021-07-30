#include "core/Error.h"

void muzzle_error(int error, const char *desc) 
{
    fprintf(stderr, "%s", desc);
}
void log_status(StatusTypes type, const char *status)
{
    switch (type)
    {
    case STATUS_FATAL_ERROR:
        fprintf(stderr, "\e[0;31m\e[4;31m[FATAL] :: %s\n\e[0m", status);
        exit(-1);
        break;
    case STATUS_WARNING:
        printf("\e[0;33m\e[4;33m[WARNING] :: %s\n\e[0m", status);
        break;

    case STATUS_ERROR:
        fprintf(stderr, "\e[0;31m\e[4;31m[ERROR] :: %s\n\e[0m", status);
        break;

    case STATUS_SUCCESS:
        printf("\e[0;32m\e[4;32m[SUCCESS] :: %s\n\e[0m", status);
        break;

    case STATUS_INFO:
        printf("\e[0;34m\e[4;34m[INFO] :: %s\n\e[0m", status);
        break;

    default:
        printf("Funny Enough. There was a unknown error when logging this status.\nIt may of been a fatal error. So because of that to be safe, we are going to still exit the application\n Sorry!! lol please report this at the github repo for Muzzle");
        exit(-1);
        break;
    }
    
}
