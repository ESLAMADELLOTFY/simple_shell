#include "shell.h"

/**
 * free_list -islam adel lotfy
 * @ptr_head: pointer adrees
 *
 * Return: void
 */
void FreeList(list_t **ptr_head)
{
	list_t *node, *next_node, *head;

	if (!ptr_head || !*ptr_head)
		return;
	head = *ptr_head;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*ptr_head = NULL;
}

/**
 * PrintListStr - print linked list 
 * @he_ad: first node pointer
 *
 * Return: size of list
 */
size_t PrintListStr(const list_t *he_ad)
{
	size_t cont = 0;

	while (he_ad)
	{
		_puts(he_ad->str ? he_ad->str : "(nil)");
		_puts("\n");
		he_ad = he_ad->next;
		cont++;
	}
	return (cont);
}

/**
 * DeleteEndAtIndex - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int DeleteEndAtIndex(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
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
 * nodeAdd - islam adel 
 * @he_ad: hefny lotfy sbd
 * @str: string asdsk skdjkls skd
 * @num: index node ro kdsd ksaa 
 *
 * Return: list size
 */
list_t *nodeAdd(list_t **he_ad, const char *str, int num)
{
	list_t *new_head;

	if (!he_ad)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *he_ad;
	*he_ad = new_head;
	return (new_head);
}

/**
 * AddNodeEnd - end list add ndex
 * @he_as: pointer address sk
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *AddNodeEnd(list_t **he_as, const char *str, int num)
{
	list_t *new_node, *node;

	if (!he_as)
		return (NULL);

	node = *he_as;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
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
		*he_as = new_node;
	return (new_node);
}

