#pragma once
#include <stdio.h> // required for fprintf()
#include <stdlib.h> // required for exit() and stderr

typedef enum StatusTypes
{
    // warning that does not affect the application much
    WARNING,
    // Error that affects the application, but does not crash it
    ERROR,
    // Error that forces the application to CTD (Crash To Desktop)
    FATAL_ERROR,
    SUCCESS,
    INFO,
} StatusTypes;


/* 
static void muzzle_error
internal error function
========================
int error
const char *desc
*/
static void muzzle_error(int error, const char *desc);
/*
void log_status
Log Status
=============
StatusTypes type
const char *status
*/
void log_status(StatusTypes type, const char *status);
