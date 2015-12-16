#include "loli.h"

// This file does not need to be edited

int main (int argc , char **argv)
{
	// First, read out all commandline arguments
	state_t *state = read_options(argc, argv);

	// Check if there is a directory specified or not
	char *work_dir = get_working_directory(argc, argv);

	// Set indent to 0 to start with no indentation
	if (state)
	{
		state->indent = 0;
	}

	list_directory(work_dir, state);

	if (state)
	{
		free(state);
	}
}
