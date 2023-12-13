#include "shell.h"

/**
 *Function: WriteHistory - Saves command history to a file
 *@information: The parameter struct
 *
 *Description: Creates a file or appends to an existing file for command hitory
 *Return: 1 on success, else -1
 */
int WriteHistory(info_t *information)
{
	ssize_t file_descriptor;
	char *file_name = GetHistoryFile(information);
	list_t *node = NULL;

	if (!file_name)
		return (-1);

	file_descriptor = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file_name);
	if (file_descriptor == -1)
		return (-1);
	for (node = information->history; node; node = node->next)
	{
		_putsfd(node->str, file_descriptor);
		_putfd('\n', file_descriptor);
	}

	_putfd(BUF_FLUSH, file_descriptor);
	close(file_descriptor);
	return (1);
}

/**
 *Function: BuildHistoryList - Adds an entry to a history linked list
 *@information: Structure containing potential arguments. Used to maintain
 *@buf: Buffer
 *@line_count: The history line count, histcount
 *
 *Return: Always 0
 */
int BuildHistoryList(info_t *information, char *buf, int line_count)
{
	list_t *node = NULL;

	if (information->history)
		node = information->history;
	add_node_end(&node, buf, line_count);

	if (!information->history)
		information->history = node;
	return (0);
}

/**
 *Function: ReadHistory - Reads command history from file
 *@information: The parameter struct
 *
 *Description: Retrieves command history from a file
 *Return: histcount on success, 0 otherwise
 */
int ReadHistory(info_t *information)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_status;
	char *buffer = NULL, *file_name = GetHistoryFile(information);

	if (!file_name)
		return (0);

	file_descriptor = open(file_name, O_RDONLY);
	free(file_name);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_status))
		file_size = file_status.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(file_descriptor, buffer, file_size);
	buffer[file_size] = '\0';
	if (read_length <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = '\0';
			BuildHistoryList(information, buffer + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		BuildHistoryList(information, buffer + last, line_count++);
	free(buffer);
	information->histcount = line_count;
	while (information->histcount-- >= HIST_MAX)
		delete_node_at_index(&(information->history), 0);
	BuildRenumberHistoryHistoryList(information);
	return (information->histcount);
}

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
			build_history_list(information, *buffer, information->histcount++);
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

		check_chain(information, buffer, &index_j, index_i, length);
		while (index_j < length)
		{
			if (is_chain(information, buffer, &index_j))
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

/**
 *Function: BuildRenumberHistoryHistoryList - Renumbers the history linked list after changes
 *@information: Structure containing potential arguments. Used to maintain
 *
 *Return: The new histcount
 */
int BuildRenumberHistoryHistoryList(info_t *information)
{
	list_t *node = information->history;
	int counter = 0;

	while (node)
	{
		node->num = counter++;
		node = node->next;
	}

	return (information->histcount = counter);
}
