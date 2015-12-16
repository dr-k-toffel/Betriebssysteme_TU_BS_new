#include <signal.h>     /* signal name macros, and the kill() prototype */
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#include "backtrace.h"

// Initialize signal handler

void initialize_signal_handler(){
    printf("init singals\n");

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGTERM, signal_handler); 
	signal(SIGABRT, signal_handler);
	signal(SIGFPE, signal_handler);
	signal(SIGSEGV, signal_handler);
}

//int sigaction (int sig_nr,const struct sigaction *handler_new,struct sigaction *handler_old); 


void signal_handler(int signal){

	printf("\nReceived Signal: %d\n", signal);
	print_backtrace();
    exit(signal);
}

void print_backtrace() 
{
    printf("___________________________________________________________________________\n");
    printf("[DEPTH] FILE(SYMBOL+OFFSET)             [ADDRESS]          [FUNCTION]\n");
    printf("___________________________________________________________________________\n");
    
    /**
     * ein mal aus der man page abschreiben ....
     * unter mac sieht das nun alles toll aus
     */

    void* callstack[MAXIMAL_BACKTRACE_DEPTH];
    int i, frames = backtrace(callstack, MAXIMAL_BACKTRACE_DEPTH);

    char** strs = backtrace_symbols(callstack, frames);
    for (i = 0; i < frames; i++)
    {
        printf("%s\n", strs[i]);
    }
    free(strs);
}
