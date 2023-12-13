#include "shell.h"

/**
 * _memset - Fills memory with a constant byte
 * @s: Pointer to the memory area
 * @b: The byte to fill *s with
 * @n: The number of bytes to be filled
 *
 * Return: A pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int index;

	for (index = 0; index < n; index++)
		s[index] = b;
	return (s);
}

/**
 * ffree - Frees a string of strings
 * @strings: String of strings
 */
void ffree(char **strings)
{
	char **temp = strings;

	if (!strings)
		return;

	while (*strings)
		free(*strings++);
	free(temp);
}

/**
 * _realloc - Reallocates a block of memory
 * @ptr: Pointer to the previous malloc'ated block
 * @old_size: Byte size of the previous block
 * @new_size: Byte size of the new block
 *
 * Return: Pointer to the old block with a new size.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}

