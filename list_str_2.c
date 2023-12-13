#include "shell.h"

/**
 * print_list - Prints all elements of a list_t linked list.
 * @head:  Pointer to the first node of the list.
 *
 * Return: Number of nodes in the list
 */
size_t print_list(const list_t *head)
{
	size_t in = 0;

	while (head)
	{
	    _puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		in++;
	}
	return (in);
}

/**
 * get_node_index - Gets the index of a node within a linked list.
 * @hd: Pointer to the list head.
 * @nd: Pointer to the node whose index needs to be found.
 *
 * Return: Index of the node (starting from 0) or -1 if node not found.
 */
ssize_t get_node_index(list_t *hd, list_t *nd)
{
	size_t count = 0;

	while (hd)
	{
		if (hd == nd)
			return (count);
		hd = hd->next;
		count++;
	}
	return (-1);
}

/**
 * list_len - determines length of linked list
 * @q: Pointer to the first node of the list.
 *
 * Return: Number of nodes in the list.
 */
size_t list_len(const list_t *q)
{
	size_t count = 0;

	while (q)
	{
		q = q->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - Converts the 'str'  in a link list to array of strings.
 * @h: Pointer to the first node of the list.
 *
 * Return: Array of strings, NULL on failure.
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t in = list_len(h), jl;
	char **str_s;
	char *str_o;

	if (!h || !in)
		return (NULL);
	str_s = malloc(sizeof(char *) * (in + 1));
	if (!str_s)
		return (NULL);
	for (in = 0; node; node = node->next, in++)
	{
		str_o = malloc(_strlen(node->str_o) + 1);
		if (!str_o)
		{
			for (j = 0; jl < in; jl++)
				free(str_s[jl]);
			free(str_s);
			return (NULL);
		}

		str_o = _strcpy(str_o, node->str_o);
		str_s[in] = str;
	}
	str_s[in] = NULL;
	return (str_s);
}

/**
 * node_starts_with - Ret node whose string starts  a given prefix
 * @no: Pointer to the list head.
 * @pre: String prefix to match.
 * @c_n: The next character after the prefix to match -1 to ignore
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *no, char *pre, char c_n)
{
	char *p = NULL;

	while (no)
	{
		p = starts_with(no->str, pre);
		if (p && ((c_n == -1) || (*p == c_n)))
			return (no);
		no = no->next;
	}
	return (NULL);
}
