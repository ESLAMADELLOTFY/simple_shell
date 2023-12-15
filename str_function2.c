#include "shell.h"

/**
 * _putchar - Writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
		write(1, buf, p);
		p = 0;
	}
	if (c != BUF_FLUSH)
		buf[p++] = c;
	return (1);
}

/**
 * _strdup - dupicates string
 * @s: to be duplicated
 *
 * Return: pointer to the duplicated string
 * It returns NULL if insufficient memory was available
 */
char *_strdup(const char *s)
{
	int length = 0;
	char *ret;

	if (s == NULL)
		return (NULL);
	while (*s++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--s;
	return (ret);
}


/**
 *_puts - function prints an input string
 *@st: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *st)
{
	int i = 0;

	if (!st)
		return;
	while (st[i] != '\0')
	{
		_putchar(st[i]);
		i++;
	}
}

/**
 * _strcpy - function that copies a string
 * @dest: the destination for the copied str.
 * @src: the soucrce string.
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int k = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[k])
	{
		dest[k] = src[k];
		k++;
	}
	dest[k] = 0;
	return (dest);
}

