#include "shell.h"

/**
 * get_node_index - get indexOf node
 * @hea_d: list hread pointer
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *hea_d, list_t *node)
{
	size_t index = 0;

	while (hea_d)
	{
		if (hea_d == node)
			return (index);
		hea_d = hea_d->next;
		index++;
	}
	return (-1);
}

/**
 * List_print - linked list Printed
 * @hd: pointer to first node
 *
 * Return: size of list
 */
size_t List_print(const list_t *hd)
{
	size_t cou = 0;

	while (hd)
	{
		_puts(convert_number(hd->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(hd->str ? hd->str : "(nil)");
		_puts("\n");
		hd = hd->next;
		cou++;
	}
	return (cou);
}

/**
 * list_To_Strings - convert array to string
 * @h_d: first node pointer
 *
 * Return: string as array
 */
char **list_To_Strings(list_t *h_d)
{
	list_t *node = h_d;
	size_t i = LenList(h_d), j;
	char **strings;
	char *str;

	if (!h_d || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}

/**
 * node_starts_with -start node with .
 * @node:list head node
 * @pree: match strings
 * @cnn: char who are the next
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *pre, char cnn)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, pre);
		if (ptr && ((cnn == -1) || (*ptr == cnn)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * LenList - lenth(linked_list)
 * @h_ead: firstNode pointer
 *
 * Return: length of list
 */
size_t LenList(const list_t *h_ead)
{
	size_t count = 0;

	while (h_ead)
	{
		h_ead = h_ead->next;
		count++;
	}
	return (count);
}

