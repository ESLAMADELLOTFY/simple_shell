#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @r:  string whose length to be printed
 *
 * Return: int length of string
 */
int _strlen(char *r)
{
	int i = 0;

	if (!r)
		return (0);

	while (*r++)
		i++;
	return (i);
}

/**
 * starts_with - function that checks whether  needle begins with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next character of haystack or NULL if otherwise
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}
/**
 * _strcat - function that concatenates dest and src
 * @dest: destnation buffer
 * @src:  source buffer
 *
 * Return: ptr to dest buffer
 */
char *_strcat(char *dest, const char *src)
{
	char *dstcpy;
	const char *srccpy;

	dstcpy = dest;
	srccpy = src;

	while (*dstcpy != '\0')
		dstcpy++;

	while (*srccpy != '\0')
		*dstcpy++ = *srccpy++;
	*dstcpy = '\0';
	return (dest);
}
/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @s_1:  first string
 * @s_2:  second string
 *
 * Return: negative if s_1 < s_2, positive if s_1 > s_2, zero if s_1 == s_2
 */
int _strcmp(char *s_1, char *s_2)
{
	while (*s_1 && *s_2)
	{
		if (*s_1 != *s_2)
			return (*s_1 - *s_2);
		s_1++;
		s_2++;
	}
	if (*s_1 == *s_2)
		return (0);
	else
		return (*s_1 < *s_2 ? -1 : 1);
}

