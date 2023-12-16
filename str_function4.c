#include "shell.h"

/**
 * STR_TOW - splits a string into words. Repeat delimiters are ignored
 * @str: the input string to be split
 * @delim: the delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **STR_TOW(char *str, char *delim)
{
	int i, j, k, m, word_count = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!delim)
		delim = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!delim_is(str[i], delim) && (delim_is(str[i + 1], delim) || !str[i + 1]))
			word_count++;

	if (word_count == 0)
		return (NULL);

	words = malloc((1 + word_count) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < word_count; j++)
	{
		while (delim_is(str[i], delim))
			i++;

		k = 0;
		while (!delim_is(str[i + k], delim) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;
	return (words);
}

/**
 * STR_TOW2 - splits a string into words using a single delimiter
 * @str: the input string to be split
 * @delim: the delimiter character
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **STR_TOW2(char *str, char delim)
{
	int i, j, k, m, word_count = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delim && str[i + 1] == delim) ||
		    (str[i] != delim && !str[i + 1]) || str[i + 1] == delim)
			word_count++;

	if (word_count == 0)
		return (NULL);

	words = malloc((1 + word_count) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < word_count; j++)
	{
		while (str[i] == delim && str[i] != delim)
			i++;

		k = 0;
		while (str[i + k] != delim && str[i + k] && str[i + k] != delim)
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];
		words[j][m] = '\0';
	}
	words[j] = NULL;
	return (words);
}
