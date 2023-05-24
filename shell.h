#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>


/* Read & Write Buffer Macros */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1



/* Commad chain macros */
#define CMD_NORM 	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/* Number conversion macros */
#define CONVERT_LOWERCASE 	1
#define CONVERT_UNSIGNED 	2


/* getlines macros */
#define USE_GETLINE 0
#define USE_STRTOK 0


/* history file macros */
#define HIST_FILE  ".simple_shell_history"
#define HIST_MAX  4096


extern char **environ;



/**
* struct liststrs - singly linked list
* @nums: the number field
* @strs: string
* @next: pointer to the next node
*/

typedef struct liststrs
{
	int nums;
	char *strs;
	struct liststrs *next;
} list_t;


/**
* struct pass_info - contains pseudo-arguments to pass into a function
* allowing uniform prototype for function pointer struct
* @arg: a string generated from getlines containing arguments
* @argv: an array of strings generated from arg
* @path: a string path for the current command
* @argc: argument count
* @line_count: the error count
* @err_nums: error code for exit()s
* @linecount_flag: if on count this line of input
* @fname: program filename
* @envs: linked list local copy of environ
* @environ: custom modified copy of environ variable from linked list envs
* @history: history node
* @alias: alias node
* @env_changed: ON if the environ variable was changed
* @status: returns the status of the last executed command
* @cmd_buff: returns the address of the pointer to cmd_buff, ON if chain
* @cmd_buff_type: CMD_type ||, &&,;
* @readfd: the fd from which to read line input
* @histcount: the history line number counter
*/

typedef struct pass_info
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_nums;
	int linecount_flag;
	char *fname;
	list_t *envs;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buff;
	int cmd_buff_type;
	int histcount;
	int readfd;
} info_t;



#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}



/**
* struct built_iin - contains a builtin string and related function
* @type: the builtin command flag
* @func: the function
*/

typedef struct built_in
{
	char *type;
	int (*func)(info_t *);
} built_in_table;



/* sh_loop.c File Prototypes*/
int hsh(info_t *, char **);
int find_built_in(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);



/* parsing.c file prototypes */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);



/* error_helper.c file prototypes */
void _eputs(char *);
int _eputchar(char);
int _putsfd(char *, int);
int _putfd(char, int);



/* exit_helper.c file prototypes */
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char *_strncpy(char *, char *, int);



/* strings_helper.c file prototypes */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
char *starts_with(const char *, const char *);



/* strings_helper1.c file prototypes */
char *_strcpy(char *, char *);
int _putchar(char);
void _puts(char *);
char *_strdup(const char *);



/* token_helper.c file prototypes */
char **strtow(char *, char *);
char **strtow2(char *, char);



/* reallocs_helper.c file prototypes */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_reallocs(void *, unsigned int, unsigned int);



/* get_envs_helper.c file prototypes */
char **get_environs(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);



/* history_helper.c file prototypes */
char *get_history_file(info_t *);
int write_history(info_t *);
int read_history(info_t *);
int build_history_list(info_t *, char *, int);
int renumber_history(info_t *);



/* lists_helper.c file prototypes */
size_t list_size(const list_t *);
char **list_to_string(list_t *);
size_t prints_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);



/* lists_helper1.c file prototypes */
size_t list_size(const list_t *);
char **list_to_string(list_t *);
size_t prints_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *head, list_t *node);



/* variables_helper.c file prototypes */
int is_chains(info_t *, char *, size_t *);
void check_chains(info_t *, char *, size_t *, size_t, size_t);
int replaces_alias(info_t *);
int replaces_vars(info_t *);
int replace_strings(char **, char *);



/* memory_helper.c file prototype */
int bfrees(void **);



/* _astoi_helper.c file prototypes */
int interact(info_t *);
int is_delimt(char, char *);
int is_alpha(int);
int _astoi(char *);



/* error1_helper.c file prototypes */
int _errastoi(char *);
void prints_error(info_t *, char *);
int print_deci(int, int);
char *converts_num(long int, int, int);
void remove_comments(char *);



/* built_in_helper.c file prototypes */
int _shellexit(info_t *);
int _shellcd(info_t *);
int _shellhelp(info_t *);



/* built_in1_helper.c file prototypes */
int _shellhistory(info_t *);
int _shellalias(info_t *);
int strset_alias(info_t *, char *);
int unstrset_alias(info_t *, char *);



/* getlines_helper.c file prototypes */
ssize_t input_buffer(info_t *, char **, size_t *);
ssize_t gets_input(info_t *);
ssize_t read_buffer(info_t *, char *, size_t *);
int _getlines(info_t *, char **, size_t *);
void s_Handler(int);



/* getinfo_helper.c file prototypes */
void clears_info(info_t *);
void sets_info(info_t *, char **);
void frees_info(info_t *, int);



/* environment.c file prototypes */
char *_getenvs(info_t *, const char *);
int _shellenv(info_t *);
int _shsetenv(info_t *);
int _shunsetenv(info_t *);
int populate_env_lists(info_t *);


#endif
