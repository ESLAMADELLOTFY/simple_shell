#include "shell.h"

/**
 *get_environment_variable environment variable
 *@information: Structure containing potential arguments. Used to maintain
 *@name: environment variable name
 *
 *Return: the value of the environment variable
 */
char *get_environment_variable(info_t *information, const char *name)
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
 *populate_env_list - populates env linked list
 *@info: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

/**
 *set_environment_variable Initialize a  variable,
 *@information: Structure containing potential arguments. Used to maintain
 *
 *Return: Always 0
 */
int set_environment_variable(info_t *information)
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
 *print_environment - prints the current environment
 *@information: Structure containing potential arguments. Used to maintain
 *Return: Always 0
 */
int print_environment(info_t *information)
{
	print_list_str(information->env);
	return (0);
}

/**
 *unset_environment_variable
 *@information: Structure containing potential.
 *
 *Return: Always 0
 */
int unset_environment_variable(info_t *information)
{
	int l;

	if (information->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (l = 1; l <= information->argc; i++)
		_unsetenv(information, information->argv[l]);

	return (0);
}
