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

/* for commands chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3


/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2


/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
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
} info_t;


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

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/* str_function2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* path_1.c */
int IsCmd(info_t *, char *);
char *DupChars(char *, int, int);
char *FindPath(info_t *, char *, char *);

/* str_function1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* mem2.c */
int bfree(void **);

/* moref1.c */
int isInteractiveMode(info_t *);
int _isDelimiter(char, char *);
int _isAlphabetic(int);
int _convertStringToInt(char *);

/* built_in_1.c */
int MyExit(info_t *);
int MyCd(info_t *);
int MyHelp(info_t *);

/* built_in_2.c */
int MyHistory(info_t *);
int MyAlias(info_t *);
int unset_user_alias(info_t *, char *);
int set_user_alias(info_t *, char *);
int print_user_alias(list_t *);
int handle_alias(info_t *);


/* information.c module */
void ClearInfo(info_t *);
void SetInfo(info_t *, char **);
void FreeInfo(info_t *, int);

/* list_str_2.c */
size_t ListLen(const list_t *);
char **listToStrings(list_t *);
size_t PrintList(const list_t *);
list_t *nodeStartsWith(list_t *, char *, char);
ssize_t GetNodeIndex(list_t *, list_t *);

/* file_ioString.c */
char *GetHistoryFile(info_t *info);
int WriteHistory(info_t *info);
int ReadHistory(info_t *info);
int BuildHistoryList(info_t *info, char *buf, int linecount);
int RenumberHistory(info_t *info);

/* moref2.c */
int Erratoi(char *);
void printErrorMessage(info_t *, char *);
int printLineNumber(int, int);
char *convertNumber(long int, int, int);
void RemoveComments(char *);


/* git_line.c */
ssize_t GetInput(info_t *);
int GetLine(info_t *, char **, size_t *);
void SigintHandler(int);


/* env_1.c */
char *Getenv(info_t *, const char *);
int Myenv(info_t *);
int Mysetenv(info_t *);
int Myunsetenv(info_t *);
int PopulateEnvList(info_t *);

/* chain_func.c */
int IsChain(info_t *, char *, size_t *);
void CheckChain(info_t *, char *, size_t *, size_t, size_t);
int ReplaceAllias(info_t *);
int ReplaceVariables(info_t *);
int ReplaceString(char **, char *);

/* env_2.c */
char **GetEnviron(info_t *);
int  Unsetenv(info_t *, char *);
int  Setenv(info_t *, char *, char *);


/* str_function4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* mem1.c */
char *Memset(char *, char, unsigned int);
void Ffree(char **);
void *Realloc(void *, unsigned int, unsigned int);




/* list_str_1.c */
list_t *AddNode(list_t **, const char *, int);
list_t *AddNodeEnd(list_t **, const char *, int);
size_t PrintListStr(const list_t *);
int DeleteNodeAtIndex(list_t **, unsigned int);
void FreeList(list_t **);

/* loophsh.c */
int LoopHsh(char **);

/* h_s_h.c */
int hsh(info_t *, char **);
int FindBuiltIn(info_t *);
void FindCmd(info_t *);
void ForkCmd(info_t *);




/* err_string_function.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

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

/* str_function3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

#endif
