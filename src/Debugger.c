#include "core/Debugger.h"

void trigger_debugger(const char* msg, debugger* self, int debug_type)
{
    switch (debug_type)
    {
    case 0:
        time_t unix_time = time(NULL);

        #ifdef MZ_DEBUGGER_LOG_OUT
        fprintf(self->log, "[%d] [%s] [\e[0;34mnatural debug] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        #endif
        fprintf(self->out, "[%d] [%s] [\e[0;34mnatural debug] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        break;
    
    case 1:
        #ifdef MZ_DEBUGGER_LOG_OUT
        fprintf(self->log, "[%d] [%s] [\e[0;33mwarning] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        #endif
        fprintf(self->err, "[%d] [%s] [\e[0;33mwarning] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        break;
    
    case 2:
        #ifdef MZ_DEBUGGER_LOG_OUT
        fprintf(self->log, "[%d] [%s] [\e[0;31merror] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        #endif
        fprintf(self->err, "[%d] [%s] [\e[0;31merror] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        break;

    case 3:
        #ifdef MZ_DEBUGGER_LOG_OUT
        fprintf(self->log, "[%d] [%s] [\e[0;31mhalt] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        #endif
        fprintf(self->err, "[%d] [%s] [\e[0;31mhalt] - %s\e[0m\n", unix_time, self->debugger_name, msg);
        getchar();
        break;
    }
}