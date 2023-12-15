#include "shell.h"

/**
 *_getenv -environment variable
 *@information: Structure containing potential arguments. Used to maintain
 *@name: environment variable name
 *
 *Return: the value of the environment variable
 */
char *_getenv(info_t *information, const char *name)
{
	list_t *node = information->env;
	char *value;

	while (node)
	{
		value = starts_with(node->str, name);
		if (value && *value)
			return (value);
		node = node->next;
	}

	return (NULL);
}

/**
 *PopulateEnvList - populates env linked list
 *@info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int PopulateEnvList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		AddNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 *_mysetenv -Initialize a  variable,
 *@information: Structure containing potential arguments. Used to maintain
 *
 *Return: Always 0
 */
int _mysetenv(info_t *information)
{
	if (information->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(information, information->argv[1], information->argv[2]))
		return (0);
	return (1);
}

/**
 *Myenv - prints the current environment
 *@information: Structure containing potential arguments. Used to maintain
 *Return: Always 0
 */
int Myenv(info_t *information)
{
	PrintListStr(information->env);
	return (0);
}

/**
 *un_mysetenv -Structure potential.
 *@information: Structure containing potential.
 *
 *Return: Always 0
 */
int un_mysetenv(info_t *information)
{
	int l;

	if (information->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (l = 1; l <= information->argc; l++)
		Unsetenv(information, information->argv[l]);

	return (0);
}

