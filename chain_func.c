#include "shell.h"

/**
 * IsChain - test if current char in buffer is a chain delimeter
 * @information: the parameter struct
 * @bufer: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int IsChain(info_t *information, char *bufer, size_t *ptr)
{
	size_t j = *ptr;

	if (bufer[j] == '|' && bufer[j + 1] == '|')
	{
		bufer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_OR;
	}
	else if (bufer[j] == '&' && bufer[j + 1] == '&')
	{
		bufer[j] = 0;
		j++;
		information->cmd_buf_type = CMD_AND;
	}
	else if (bufer[j] == ';') /* found end of this command */
	{
		bufer[j] = 0; /* replace semicolon with null */
		information->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}

/**
 * CheckChain - checks we should continue chaining based on last status
 * @information: the parameter struct
 * @buf: the char buffer
 * @ptr: address of current position in buf
 * @i: starting position in buf
 * @l: length of buf
 *
 * Return: Void
 */
void CheckChain(info_t *information, char *buf, size_t *ptr, size_t i, size_t l)
{
	size_t m = *ptr;

	if (information->cmd_buf_type == CMD_AND)
	{
		if (information->status)
		{
			buf[i] = 0;
			m = l;
		}
	}
	if (information->cmd_buf_type == CMD_OR)
	{
		if (!information->status)
		{
			buf[i] = 0;
			m = l;
		}
	}

	*ptr = m;
}

/**
 * ReplaceAllias - replaces an aliases in the tokenized string
 * @information: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceAllias(info_t *information)
{
	int index;
	list_t *node;
	char *ptr;

	for (index = 0; index < 10; index++)
	{
		node = nodeStartsWith(information->alias, information->argv[0], '=');
		if (!node)
			return (0);
		free(information->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		information->argv[0] = ptr;
	}
	return (1);
}

/**
 * ReplaceVariables - replaces vars in the tokenized string
 * @in_fo: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int ReplaceVariables(info_t *in_fo)
{
	int index = 0;
	list_t *node;

	for (index = 0; in_fo->argv[index]; index++)
	{
		if (in_fo->argv[index][0] != '$' || !in_fo->argv[index][1])
			continue;

		if (!_strcmp(in_fo->argv[index], "$?"))
		{
			ReplaceString(&(in_fo->argv[index]),
				_strdup(convert_number(in_fo->status, 10, 0)));
			continue;
		}
		if (!_strcmp(in_fo->argv[index], "$$"))
		{
			ReplaceString(&(in_fo->argv[index]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(in_fo->env, &in_fo->argv[index][1], '=');
		if (node)
		{
			ReplaceString(&(in_fo->argv[index]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		ReplaceString(&in_fo->argv[index], _strdup(""));

	}
	return (0);
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
