#include "shell.h"


/**
 *Function: sigintHandler - blocks ctrl-C
 *@signal_num: the signal number
 *
 *Description: Handles the interrupt signal (SIGINT).
 *Return: Void
 */
void sigintHandler(__attribute__((unused)) int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 *Function: readBuffer - reads a buffer
 *@information: parameter struct
 *@buffer: buffer
 *@size_i: size
 *
 *Description: Reads a buffer and returns the size read.
 *Return: Size read
 */
ssize_t readBuffer(info_t *information, char *buffer, size_t *size_i)
{
	ssize_t bytes_read = 0;

	if (*size_i)
		return (0);
	bytes_read = read(information->readfd, buffer, READ_BUF_SIZE);
	if (bytes_read >= 0)
		*
		size_i = bytes_read;
	return (bytes_read);
}

/**
 *Function: GetLine - gets the next line of input from STDIN
 *@information: parameter struct
 *@ptr: address of pointer to buffer, preallocated or NULL
 *@length: size of preallocated ptr buffer if not NULL
 *
 *Description: Gets the next line of input.
 *Return: Size of input
 */
int GetLine(info_t *information, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t index_i, len;
	size_t k;
	ssize_t bytes_read = 0, size_read = 0;
	char *pointer_p = NULL, *new_pointer_p = NULL, *c;

	pointer_p = *ptr;
	if (pointer_p && length)
		size_read = *length;
	if (index_i == len)
		index_i = len = 0;

	bytes_read = readBuffer(information, buffer, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + index_i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_pointer_p = _realloc(pointer_p, size_read, size_read ? size_read + k : k + 1);
	if (!new_pointer_p)
		return (pointer_p ? (free(pointer_p), -1) : -1);

	if (size_read)
		_strncat(new_pointer_p, buffer + index_i, k - index_i);
	else
		_strncpy(new_pointer_p, buffer + index_i, k - index_i + 1);

	size_read += k - index_i;
	index_i = k;
	pointer_p = new_pointer_p;

	if (length)
		*
		length = size_read;
	*ptr = pointer_p;
	return (size_read);
}

/**
 *Function: bufferInput - buffers chained commands
 *@information: parameter struct
 *@buffer: address of buffer
 *@length: address of len var
 *
 *Description: Reads input into buffer, processes chained commands.
 *Return: Bytes read
 */
ssize_t bufferInput(info_t *information, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t length_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigintHandler);
		#if USE_GETLINE
		bytes_read = getline(buffer, &length_p, stdin);
		#else
			bytes_read = GetLine(information, buffer, &length_p);
		#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{ 	(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}

			information->linecount_flag = 1;
			remove_comments(*buffer);
			BuildRenumberHistoryHistoryList(information, *buffer, information->histcount++);
			if (_strchr(*buffer, ';'))
			{ 	*length = bytes_read;
				information->cmd_buf = buffer;
			}
		}
	}

	return (bytes_read);
}

/**
 *Function: GetInput - gets a line minus the newline
 *@information: parameter struct
 *
 *Description: Obtains input, processes chained commands if any.
 *Return: Bytes read
 */
ssize_t GetInput(info_t *information)
{
	static char *buffer;
	static size_t index_i, index_j, length;
	ssize_t bytes_read = 0;
	char **buffer_p = &(information->arg), *pointer_p;

	_putchar(BUF_FLUSH);
	bytes_read = bufferInput(information, &buffer, &length);
	if (bytes_read == -1)
		return (-1);
	if (length)
	{
		index_j = index_i;
		pointer_p = buffer + index_i;

		CheckChain(information, buffer, &index_j, index_i, length);
		while (index_j < length)
		{
			if (IsChain(information, buffer, &index_j))
				break;
			index_j++;
		}

		index_i = index_j + 1;
		if (index_i >= length)
		{
			index_i = length = 0;
			information->cmd_buf_type = CMD_NORM;
		}

		*buffer_p = pointer_p;
		return (_strlen(pointer_p));
	}

	*buffer_p = buffer;
	return (bytes_read);
}
