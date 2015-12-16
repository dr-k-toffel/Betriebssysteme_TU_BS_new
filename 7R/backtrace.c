#include <signal.h>     /* signal name macros, and the kill() prototype */
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>

#include "backtrace.h"

// Initialize signal handler
void initialize_signal_handler(){

	signal(SIGINT, signal_handler); // Interrupt from keyboard
	signal(SIGQUIT, signal_handler); // Quit from keyboard
	signal(SIGILL, signal_handler); //Illegal instruction
	signal(SIGTERM, signal_handler); // Termination signal 
	signal(SIGABRT, signal_handler); //Abort signal from abort(3)
	signal(SIGFPE, signal_handler); // Floating point exception
	signal(SIGSEGV, signal_handler); // Invalid memory reference
}

void signal_handler(int signal){

	printf("\nReceived Signal: %d\n", signal); // print signal number
	print_backtrace();
	exit(signal); // terminate programm and return signal number
}

void print_backtrace(){

	printf("___________________________________________________________________________\n");
	printf("[DEPTH] FILE(SYMBOL+OFFSET)             [ADDRESS]          [FUNCTION]\n");
	printf("___________________________________________________________________________\n");
    

	void* callstack[MAXIMAL_BACKTRACE_DEPTH]; // alloced memory
	int frames = backtrace(callstack, MAXIMAL_BACKTRACE_DEPTH);//  get call stack count and call stack content
	char** strs = backtrace_symbols(callstack, frames); // make call stack content readabl
	for (int i = 0; i < frames; i++){
		printf("%s\n", strs[i]);
	}
	free(strs);
}
