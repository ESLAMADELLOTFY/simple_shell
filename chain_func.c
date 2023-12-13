#include "shell.h"

/**
 * Function: ReplaceAllias - replaces an alias in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceAllias(info_t *information)
{
	int i;
	list_t *node;
	char *pointer;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(information->alias, information->arguments[0], '=');
		if (!node)
			return (0);
		free(information->arguments[0]);
		pointer = _strchr(node->str, '=');
		if (!pointer)
			return (0);
		pointer = _strdup(pointer + 1);
		if (!pointer)
			return (0);
		information->arguments[0] = pointer;
	}
	return (1);
}

/**
 * Function: CheckChain - checks if we should continue
 * @information: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 * @start: starting position in buffer
 * @length: length of buffer
 *
 * Return: Void
 */
void CheckChain(info_t *information, char *buffer, size_t *position, size_t start, size_t length)
{
	size_t j = *position;

	if (information->command_buffer_type == CMD_AND)
	{
		if (information->status)
		{
			buffer[start] = 0;
			j = length;
		}
	}
	if (information->command_buffer_type == CMD_OR)
	{
		if (!information->status)
		{
			buffer[start] = 0;
			j = length;
		}
	}

	*position = j;
}

/**
 * Function: IsChain - test if current
 * @information: the parameter struct
 * @buffer: the char buffer
 * @position: address of current position in buffer
 *
 * Return: 1 if command delimiter, 0 otherwise
 */
int IsChain(info_t *information, char *buffer, size_t *position)
{
	size_t j = *position;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		information->command_buffer_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + IsChainer[j] = 0;
		j++;
		information->command_buffer_type = CMD_AND;
	}
	else if (buffer[j] == ';') /* found end of this command */
	{
		buffer[j] = 0; /* replace semicolon with null */
		information->command_buffer_type = CMD_CHAIN;
	}
	else
		return (0);
	*position = j;
	return (1);
}

/**
 * ReplaceString - replaces string
 * @o: address of old string
 * @n: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceString(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}

/**
 * Function: ReplaceVariables - replaces variables in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceVariables(info_t *information)
{
	int i = 0;
	list_t *node;

	for (i = 0; information->argument[i]; i++)
	{
		if (information->argument[i][0] != '$' || !information->argument[i][1])
			continue;

		if (!_strcmp(information->argument[i], "$?"))
		{
			ReplaceString(&(information->argument[i]),
				_strdup(convert_number(information->status, 10, 0)));
			continue;
		}
		if (!_strcmp(information->argument[i], "$$"))
		{
			ReplaceString(&(information->argument[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(information->env, &information->argument[i][1], '=');
		if (node)
		{
			ReplaceString(&(information->argument[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
			ReplaceString(&information->argument[i], _strdup(""));
	}
	return (0);
}
