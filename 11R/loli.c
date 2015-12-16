#include "loli.h"

// Returns 1 if the entry is a directory, 0 otherwise
int is_dir(const struct dirent *entry){
	//write your code here
	return 0;
}

// Returns 1 if the entry is not a directory, 0 otherwise
int is_not_dir(const struct dirent *entry){
	//write your code here
	return 0;
}

// 11.1 & 11.2
char *get_working_directory(int argc, char **argv)
{

	// das letzte argument holen
	int c;
	while ((c = (int)getopt(argc, argv, "alRh:")) != 1)
	{
		if (c == -1) { // warum auch immer die schleife durch laueft v_v
			break;
		}
	}

	if (argv[optind] != NULL) 
	{
		return argv[optind];
	}

	char* buffer = (char*) calloc(PATHLENGTH, sizeof(char));
	if (!buffer) 
	{
		perror("calloc");
		exit(-1);
	}
	//write your code here
	return getcwd(buffer, PATHLENGTH);
}

// 11.1 & 11.4 & 11.5
void list_directory(char const *directory, state_t *state)
{
	//access() is a potential security hole and should never be used.
	// <3

	// testen ob leserechte existieren
	if (access(directory, R_OK) == 0) 
	{
		// ornder oeffnen
		DIR* dir = opendir(directory);
		if (dir) 
		{
			struct dirent* de;
			while ((de = readdir(dir)) != NULL)
			{
				if (state->all || de->d_name[0] != '.') 
				{
					struct stat info;

					if (lstat(de->d_name, &info) == 0) 
					{
						char* fileInfo = get_entry_string(&info, de->d_name, state); 
						printf("%s\n", fileInfo);
						free(fileInfo);

						if (state->recursive && state->indent < 10 && S_ISDIR(info.st_mode)) 
						{
							state->indent++;
							list_directory(de->d_name, state);
							state->indent--;
						}
					}
					else
					{
						perror("lstat");
						exit(-1);
					}
				}
			}
			closedir(dir);
		}
	}
	//write your code here
	return;
}

// 11.1 & 11.3 & 11.4 & 11.5
char *get_entry_string(struct stat *entry_info, char const *entry, state_t *state)
{
	//write your code here
	//size_t size = strlen(entry);
	char* buffer = (char*) calloc(2047, sizeof(char));
	if (!buffer) 
	{
		perror("calloc");
		exit(-1);
	}

	if (state->long_form) {
		char *mode = get_mode_string(entry_info->st_mode);
		char *owner = get_owner_string(entry_info->st_uid, entry_info->st_gid);
		char *time = get_time_string(entry_info->st_mtime);

		char format [40];
		sprintf(format, "%s%d%s", "%s %2d %s %10lld %s %", 4 * state->indent ,"s%s");
		sprintf(buffer, format, mode, entry_info->st_nlink, owner, entry_info->st_size, time, "", entry);

		free(mode);
		free(owner);
		free(time);	
	}
	else
	{
		sprintf(buffer, "%s", entry);
	}
	
	//write your code here
	
	return buffer;
}

// 11.2
state_t *read_options(int argc , char **argv)
{
	state_t* state = (state_t*) calloc(1, sizeof(state_t));
	if (!state) 
	{
		perror("calloc");
		exit(-1);
	}

	int c;

	while ((c = (int)getopt(argc, argv, "alRh:")) != 1)
	{
		if (c == -1) { // warum auch immer die schleife durch laueft v_v
			break;
		}
		switch(c)
		{
			case 'a' :
				state->all = 1;
				break;
			case 'l' :
				state->long_form = 1;
				break;
			case 'R' :
			 	state->recursive = 1;
			 	break;
			case 'h' :
			case '?' :
				printf("-a zeigt alle Datien an\n");
				printf("-l zeigt zusaetzliche Eigenschaften an\n");
				printf("-R geht Rekursiv in die Unterverzeichnisse\n");
				printf("-h zeigt diese Hilfe an\n");
				exit(0);
				break;
			default :
				break;
		}
	}

	//printf("%d ende\n", optind);

	argv += optind;

	//printf("letzte: %s\n", argv[0]);
	
	//write your code here
	return state;
}

// 11.4
char *get_mode_string(mode_t mode)
{
	char c;
	switch (mode & S_IFMT) 
	{
       	case S_IFBLK:  
       		c = 'b';
       	    break;
        case S_IFCHR:  
        	c = 'c';
        	break;
        case S_IFDIR:  
        	c = 'd';
        	break;
        case S_IFIFO: 
        	c = 'p';
        	break;
        case S_IFLNK: 
        	c = 'l';
        	break;
        case S_IFREG: 
        	c = '-';
        	break;
        case S_IFSOCK:
        	c ='s';
        	break;
        default:
        	c = '?';   
        	break;
    }
    
    char p1 = (mode & S_IRUSR) ? 'r' : '-';
    char p2 = (mode & S_IWUSR) ? 'w' : '-';
	char p3 = (mode & S_IXUSR) ? 'x' : '-';
	char p4 = (mode & S_IRGRP) ? 'r' : '-';
	char p5 = (mode & S_IWGRP) ? 'w' : '-';
	char p6 = (mode & S_IXGRP) ? 'x' : '-';
	char p7 = (mode & S_IROTH) ? 'r' : '-';
	char p8 = (mode & S_IWOTH) ? 'w' : '-';
	char p9 = (mode & S_IXOTH) ? 'x' : '-';

	char *buffer = (char*) calloc(10, sizeof(char));
	if (!buffer) 
	{
		perror("calloc");
		exit(-1);
	}

	buffer[0] = c;
	buffer[1] = p1;
	buffer[2] = p2;
	buffer[3] = p3;
	buffer[4] = p4;
	buffer[5] = p5;
	buffer[6] = p6;
	buffer[7] = p7;
	buffer[8] = p8;
	buffer[9] = p9;

	//write your code here
	return buffer;
}

// 11.4
char *get_owner_string(uid_t user_id, gid_t group_id)
{
	struct passwd *user = getpwuid(user_id);
	struct group *group = getgrgid(group_id);
	
	char *buffer = (char*) calloc(strlen(user->pw_name) + 1 + strlen(group->gr_name), sizeof(char));
	if (!buffer) 
	{
		perror("calloc");
		exit(-1);
	}

	sprintf(buffer, "%s %s", user->pw_name, group->gr_name);

	//write your code here
	return buffer;
}

// 11.4
char *get_time_string(time_t time)
{
	struct tm *ltime = localtime(&time);
	
	char *buffer = (char*) calloc(80, sizeof(char));
	if (!buffer) 
	{
		perror("calloc");
		exit(-1);
	}
	strftime(buffer,80,"%a %b %d %H:%M:%S %Y", ltime);

	//free(ltime);l
	//write your code here
	return buffer;
}
