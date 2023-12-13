#include "shell.h"

/**
 * Function: handle_alias - mimics the alias builtin (man alias)
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int handle_alias(info_t *data)
{
	int i = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_user_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		ptr = _strchr(data->argv[i], '=');
		if (ptr)
			set_user_alias(data, data->argv[i]);
		else
			print_user_alias(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}

/**
 * Function: print_user_alias - prints an alias string
 * @list_node: the alias node
 *
 * Return: 0 on success, 1 on error
 */
int print_user_alias(list_t *list_node)
{
	char *ptr = NULL, *alias_val = NULL;

	if (list_node)
	{
		ptr = _strchr(list_node->str, '=');
		for (alias_val = list_node->str; alias_val <= ptr; alias_val++)
			_putchar(*alias_val);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * Function: display_history - displays the history list,
 *                             with line numbers, starting at 0.
 * @data: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * Function: set_user_alias - sets an alias string
 * @data: parameter struct
 * @str_val: the string alias
 *
 * Return: 1 on error, 0 on success
 */
int set_user_alias(info_t *data, char *str_val)
{
	char *ptr;

	ptr = _strchr(str_val, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_user_alias(data, str_val));

	unset_user_alias(data, str_val);
	return (add_node_end(&(data->alias), str_val, 0) == NULL);
}

/**
 * Function: unset_user_alias - unsets an alias string
 * @data: parameter struct
 * @str_val: the string alias
 *
 * Return: 1 on error, 0 on success
 */
int unset_user_alias(info_t *data, char *str_val)
{
	char *ptr, ch;
	int ret;

	ptr = _strchr(str_val, '=');
	if (!ptr)
		return (1);
	ch = *ptr;
	*ptr = 0;
	ret = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, str_val, -1)));
	*ptr = ch;
	return (ret);
}


