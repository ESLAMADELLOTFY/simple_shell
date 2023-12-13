#include "shell.h"

/**
 * free_list - Frees memory allocated for all nodes of a linked list.
 * @h_ptr: Address of pointer to the head node of the list.
 *
 * Return: void
 */
void free_list(list_t **h_ptr)
{
	list_t *node, *next_node, *head;

	if (!h_ptr || !*h_ptr)
		return;
	head = *h_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*h_ptr = NULL;
}

/**
 * add_node - Adds a new node to the beginning of the linked list.
 * @head: Address of pointer to the head node of the list.
 * @str_value: String value to be stored in the node.
 * @index: Node index used in history.
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str_value, int index)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->index = index;
	if (str_value)
	{
		new_head->str_value = _strdup(str_value);
		if (!new_head->str_value)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * delete_node_at_index - Deletes a node at a given index in a linked list.
 * @h: Address of pointer to the first node.
 * @j: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **h, unsigned int j)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!j)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == j)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * add_node_end - Adds a node to the end of the linked list.
 * @head: Address of pointer to the head node of the list.
 * @str_value: String value to be stored in the node.
 * @index: Node index used in history.
 *
 * Return: Pointer to the newly added node, NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str_value, int index)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;
	if (str_value)
	{
		new_node->str_value = _strdup(str_value);
		if (!new_node->str_value)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - Prints only the 'str' element of node in a  list.
 * @q: Pointer to the first node of the list.
 *
 * Return: Number of nodes in the list.
 */
size_t print_list_str(const list_t *q)
{
	size_t j = 0;

	while (q)
	{
		_puts(q->str ? q->str : "(nil)");
		_puts("\n");
		q = q->next;
		j++;
	}
	return (j);
}

