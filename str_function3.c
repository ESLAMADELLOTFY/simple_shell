#include "shell.h"

/**
 **_strchr - locates a character in a string
 *@st: string to be checked
 *@c: character to be located
 *Return: returns pointer to first occurence of character
 *or NULL if character not found
 */
char *_strchr(char *st, char c)
{
	do {
		if (*st == c)
			return (st);
	} while (*st++ != '\0');

	return (NULL);
}

/**
 * _strncat - concatenates n characters from src to dest
 * @dest: destination string
 * @src: source string
 * @n: maximum number of characters to concatenate from src
 * Return: returns pointer to the destination string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, l;
	char *s = dest;

	i = 0;
	l = 0;
	while (dest[i] != '\0')
		i++;
	while (src[l] != '\0' && l < n)
	{
		dest[i] = src[l];
		i++;
		l++;
	}
	if (l < n)
		dest[i] = '\0';
	return (s);
}

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

