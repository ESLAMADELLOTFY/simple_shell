#include "shell.h"

/**
 * _convertStringToInt - Converts a string to an integer
 * @str: The string to be converted
 *
 * This function converts a string to an integer.
 * If no numbers are found in the string, it returns 0.
 *
 * Return: The converted integer or 0 if no numbers are found
 */
int _convertStringToInt(char *str)
{
	int index = 0, sign = 1, flag = 0, result = 0;

	while (str[index] != '\0' && flag != 2)
	{
		if (str[index] == '-')
			sign *= -1;

		if (str[index] >= '0' && str[index] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[index] - '0');
		}
		else if (flag == 1)
			flag = 2;

		index++;
	}

	return (sign * result);
}

/**
 * _isDelimiter - Checks if a character is a delimiter
 * @c: The character to check
 * @delimiter: The delimiter string
 *
 * This function checks if a character is a delimiter,
 * comparing it to the provided delimiter string.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise
 */
int _isDelimiter(char c, char *delimiter)
{
	while (*delimiter)
	{
		if (*delimiter == c)
			return (1);
		delimiter++;
	}

	return (0);
}

/**
 * isInteractiveMode - Checks if the shell is in interactive mode
 * @info: Pointer to info_t structure
 *
 * This function determines whether the shell is in interactive mode
 * by verifying if the standard input is associated with a terminal.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise
 */
int isInteractiveMode(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * _isAlphabetic - Checks for an alphabetic character
 * @c: The character to check
 *
 * This function checks whether the provided character is alphabetic.
 *
 * Return: 1 if the character is alphabetic, 0 otherwise
 */
int _isAlphabetic(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
