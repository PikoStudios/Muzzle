#pragma once
#include <stdio.h> // required for fprintf()
#include <stdlib.h> // required for exit() and stderr
#include "../backend.h" // Required for MZ_API

typedef enum StatusTypes
{
    // warning that does not affect the application much
    STATUS_WARNING,
    // Error that affects the application, but does not crash it
    STATUS_ERROR,
    // Error that forces the application to CTD (Crash To Desktop)
    STATUS_FATAL_ERROR,
    STATUS_SUCCESS,
    STATUS_INFO,
} StatusTypes;

typedef enum ErrorResult
{
    FAILED,
    WORKED
} ErrorResult;


#ifdef __cplusplus
extern "C" {
#endif


/* 
void muzzle_error
internal error function
========================
int error
const char *desc
*/
MZ_API void muzzle_error(int error, const char *desc);
/*
void log_status
Log Status
=============
StatusTypes type
const char *status
*/
MZ_API void log_status(StatusTypes type, const char *status);
/*
void log_fatal
Log Fatal Staus
=============
const char *status
const char *func_name
*/
MZ_API void log_fatal(const char* status, const char* func_name);

#ifdef __cplusplus
}
#endif
