#include "shell.h"

/**
 * Function: change_directory - changes the current directory of the process
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int change_directory(info_t *data)
{
	char *cwd, *new_dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		new_dir = _getenv(data, "HOME=");
		if (!new_dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((new_dir = _getenv(data, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(cwd);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((new_dir = _getenv(data, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * Function: display_help - displays help information
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_help(info_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * Function: exit_shell - exits the shell
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: exits with a given exit status
 *         (0) if data.argv[0] != "exit"
 */
int exit_shell(info_t *data)
{
	int exit_status;

	if (data->argv[1])  /* If there is an exit argument */
	{
		exit_status = _erratoi(data->argv[1]);
		if (exit_status == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}
		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}


