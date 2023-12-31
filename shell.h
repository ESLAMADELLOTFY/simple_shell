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

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
}info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
void ForkCmd(info_t *);
void find_cmd(info_t *);
int FindBuiltIn(info_t *);
void fork_cmd(info_t *);
int h_s_h(info_t *in_fo, char **av);
/* path.c */
int IsCmd(info_t *information, char *file_path);
char *DupChars(char *path_string, int start_index, int stop_index);
char *FindPath(info_t *info_struct, char *path_string, char *command);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* string_functions4.c */
char **STR_TOW(char *, char *);
char **STR_TOW2(char *, char);

/* memory_functions */
char *Memset(char *, char, unsigned int);
void Ffree(char **);
void *Realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int be_free(void **);

/* more_functions.c */
int isInteractiveMode(info_t *);
int delim_is(char, char *);
int _isAlphabetic(int);
int _convertStringToInt(char *);

/* more_functions2.c */
int Erratoi(char *);
void print_error(info_t *info, char *estr);
int printLineNumber(int num, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* built_in_2.c */
int help_me(info_t  *);
int cd_my(info_t  *);
int exsit_me(info_t  *);

/* built_in_1.c */
int handle_alias(info_t *);
int print_user_alias(list_t *);
int MyHistory(info_t *);
int set_user_alias(info_t *data, char *);
int unset_user_alias(info_t *data, char *);

/* getline.c module */
ssize_t readBuffer(info_t *, char *, size_t *);
int GetLine(info_t *, char **, size_t *);
ssize_t bufferInput(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t GetInput(info_t *);

/* info.c module */
void SetInfo(info_t *, char **);
void ClearInfo(info_t *);
void FreeInfo(info_t *, int);

/* env.c module */
char *_getenv(info_t *, const char *);
int Myenv(info_t *);
int _mysetenv(info_t *);
int un_mysetenv(info_t *);
int PopulateEnvList(info_t *);

/* env2.c module */
char **GetEnviron(info_t *);
int Unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_functions.c */
char *GetHistoryFile(info_t *info);
int WriteHistory(info_t *);
int ReadHistory(info_t *);
int BuildRenumberHistoryHistoryList(info_t *);
int BuildHistoryList(info_t *, char *buf, int );

/* liststr.c module */
list_t *add_node(list_t **, const char *, int);
list_t *AddNodeEnd(list_t **, const char *, int);
size_t PrintListStr(const list_t *);
int DeleteEndAtIndex(list_t **, unsigned int);
void FreeList(list_t **);

/* liststr2.c module */
ssize_t get_node_index(list_t *hea_d, list_t *node);
size_t List_print(const list_t *hd);
char **list_To_Strings(list_t *h_d);
list_t *node_starts_with(list_t *node, char *pre, char cnn);
size_t LenList(const list_t *h_ead);

/* chain.c */
int IsChain(info_t *, char *, size_t *);
void CheckChain(info_t *, char *, size_t *, size_t , size_t );
int ReplaceAllias(info_t *);
int ReplaceVariables(info_t *);
int replaceString(char **, char *);
#endif
