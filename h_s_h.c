#include "shell.h"

/**
 * ForkCmd- Executes a command found in the PATH environment variable.
 * @information: the parameter & return info struct
 *
 * Return: void
 */
void ForkCmd(info_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(information->path, information->argv, get_environ(information)) == -1)
		{
			free_info(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(information->status));
		if (WIFEXITED(information->status))
		{
			information->status = WEXITSTATUS(information->status);
			if (information->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}

/**
 * find_cmd - Finds a command in and executes it.
 * @information: Pointer to the info struct.
 *
 * Return: void
 */
void find_cmd(info_t *information)
{
	char *path = NULL;
	int l, q;

	information->path = information->argv[0];
	if (information->linecount_flag == 1)
	{
		information->line_count++;
		information->linecount_flag = 0;
	}
	for (l = 0, q = 0; information->arg[l]; l++)
		if (!is_delim(information->arg[l], " \t\n"))
			q++;
	if (!q)
		return;

	path = find_path(information, _getenv(information, "PATH="), information->argv[0]);
	if (path)
	{
		information->path = path;
		ForkCmd(information);
	}
	else
	{
		if ((interactive(information) || _getenv(information, "PATH=")
			|| information->argv[0][0] == '/') && is_cmd(information, information->argv[0]))
			ForkCmd(information);
		else if (*(information->arg) != '\n')
		{
			information->status = 127;
			print_error(information, " it doesn't not found\n");
		}
	}
}

/**
 * FindBuiltIn - Finds and executes if available.
 * @information: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int FindBuiltIn(info_t *information)
{
	int i, builtinret = -1;
	builtin_table builtInTabl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtInTabl[i].type; i++)
		if (_strcmp(information->argv[0], builtInTabl[i].type) == 0)
		{
			information->line_count++;
			builtinret = builtInTabl[i].func(information);
			break;
		}
	return (builtinret);
}
