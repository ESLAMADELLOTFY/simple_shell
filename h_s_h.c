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
		if (execve(information->path, information->argv, GetEnviron(information)) == -1)
		{
			FreeInfo(information, 1);
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
		if (!delim_is(information->arg[l], " \t\n"))
			q++;
	if (!q)
		return;

	path = where_path(information, _getenv(information, "PATH="), information->argv[0]);
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
		{"exit", exsit_me},
		{"env", Myenv},
		{"help", help_me},
		{"history", MyHistory},
		{"setenv", _mysetenv},
		{"unsetenv", un_mysetenv},
		{"cd", cd_my},
		{"alias", handle_alias},
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

/**
 * h_s_h - loop of main shell
 * @in_fo: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int h_s_h(info_t *in_fo, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		ClearInfo(in_fo);
		if (interactive(in_fo))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = GetInput(in_fo);
		if (r != -1)
		{
			SetInfo(in_fo, av);
			builtin_ret = FindBuiltIn(in_fo);
			if (builtin_ret == -1)
				find_cmd(in_fo);
		}
		else if (interactive(in_fo))
			_putchar('\n');
		FreeInfo(in_fo, 0);
	}
	WriteHistory(in_fo);
	FreeInfo(in_fo, 1);
	if (!interactive(in_fo) && in_fo->status)
		exit(in_fo->status);
	if (builtin_ret == -2)
	{
		if (in_fo->err_num == -1)
			exit(in_fo->status);
		exit(in_fo->err_num);
	}
	return (builtin_ret);
}
