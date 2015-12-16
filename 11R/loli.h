#ifndef __LOLI_H__
#define __LOLI_H__

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>         //getopt
#include <sys/types.h>      //stat
#include <sys/stat.h>       //stat
#include <unistd.h>         //stat
#include <dirent.h>         //dir stuff
#include <time.h>
#include <pwd.h>            //username
#include <grp.h>            //gruppenname
#include <string.h>         //strcat

#define PATHLENGTH 1024

#ifndef __State
#define __State
typedef struct
{
	int all; // Indictates, that all files should be displayed
	int long_form; // Indicates, that entry information should be displayed
	int recursive; // Indicates, that all subfolders should be displayed
	int indent; // Used for counting the indent level/depth
} state_t;
#endif

// Reads in all options and returns a State struct with the appropriate flags set, don't forget to free the memory
state_t *read_options(int argc , char **argv);

char *get_working_directory(int argc, char **argv);

// Returns a char* with the file modes and access, don't forget to free the memory
char *get_mode_string(mode_t mode);

// Returns a char* with the names of the owner user and group, don't forget to free the memory
char *get_owner_string(uid_t user_id, gid_t group_id);

// Returns a char* with the formatted time, don't forget to free the memory
char *get_time_string(time_t time);

// Returns a char* with the formatted entry, ready to print.
// If state.long_form is set, this should look like a line from ls -l
// otherwise like normal ls, except that every entry is on its own line.
char *get_entry_string(struct stat *entry_info, char const *entry, state_t *state);

// Iterated through every entry in the given directory and prints it out using get_entry_string
// If state.all is set, entries starting with a dot (.) should be included, otherwiese not.
// If state.sort is set, output should be alphabetically sorted, starting with directories.
// If state.recursive is set, all subfolders should also be travers and outputtet.
void list_directory(char const *directory, state_t *state);

#endif
