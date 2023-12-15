#include "shell.h"

/**
 * _eputchar -Writes the character c to the error output (stderr).
 * @p: The character to be printed.
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int _eputchar(char p)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(2, buf, l);
		l = 0;
	}
	if (p != BUF_FLUSH)
		buf[l++] = p;
	return (1);
}

/**
 * _putfd -  Writes the  'c' to the given file descriptor 'fd'.
 * @p: The character to print
 * @f_d: The filedescriptor to write to
 *
 * Return: On success, returns 1.
 * On error, returns -1, and errno is set appropriately.
 */
int _putfd(char p, int f_d)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (p == BUF_FLUSH || l >= WRITE_BUF_SIZE)
	{
		write(f_d, buf, l);
		l = 0;
	}
	if (p != BUF_FLUSH)
		buf[l++] = p;
	return (1);
}

/**
 *_eputs - Prints an input string to the standard error output.
 * @str_value: The string to be printed.
 *
 * Return: Nothing
 */
void _eputs(char *str_value)
{
	int z = 0;

	if (!str_value)
		return;
	while (str_value[z] != '\0')
	{
		_eputchar(str_value[z]);
		z++;
	}
}

/**
 *_putsfd - Prints an input string to the specified file descriptor.
 * @str_value: the string to be printed
 * @f_d: The file descriptor to write to.
 *
 * Return: the number of chars put
 */
int _putsfd(char *str_value, int f_d)
{
	int l = 0;

	if (!str_value)
		return (0);
	while (*str_value)
	{
		l += _putfd(*str_value++, f_d);
	}
	return (l);
}

