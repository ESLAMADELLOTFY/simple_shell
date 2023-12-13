#include "shell.h"

/**
 *Function: set_environment_variable - Initialize a new environment variable,
 *                                     or modify an existing one
 *@information: Structure containing potential arguments. Used to maintain
 *@varia: the string environment variable property
 *@value: the string environment variable value
 *Return: Always 0
 */
int set_environment_variable(info_t *information, char *varia, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *pointer;

	if (!varia || !value)
		return (0);

	buffer = malloc(_strlen(varia) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, varia);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = information->env;
	while (node)
	{
		pointer = starts_with(node->str, varia);
		if (pointer && *pointer == '=')
		{
			free(node->str);
			node->str = buffer;
			information->env_changed = 1;
			return (0);
		}

		node = node->next;
	}

	add_node_end(&(information->env), buffer, 0);
	free(buffer);
	information->env_changed = 1;
	return (0);
}

/**
 *Function: unset_environment_variable - Remove an environment variable
 *@information: Structure containing potential arguments. Used to maintain
 *Return: 1 on delete, 0 otherwise
 *@varia: the string environment variable property
 */
int unset_environment_variable(info_t *information, char *varia)
{
	list_t *node = information->env;
	size_t i = 0;
	char *pointer;

	if (!node || !varia)
		return (0);

	while (node)
	{
		pointer = starts_with(node->str, varia);
		if (pointer && *pointer == '=')
		{
			information->env_changed = delete_node_at_index(&(information->env), i);
			i = 0;
			node = information->env;
			continue;
		}

		node = node->next;
		i++;
	}

	return (information->env_changed);
}

/**
 *Function: get_environment - returns the string array copy of our environment
 *@information: Structure containing potential arguments. Used to maintain
 *Return: Pointer to the environment strings array
 */
char **get_environment(info_t *information)
{
	if (!information->environ || information->env_changed)
	{
		information->environ = list_to_strings(information->env);
		information->env_changed = 0;
	}

	return (information->environ);
}
