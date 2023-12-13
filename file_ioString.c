#include "shell.h"

/**
 *Function: write_history - Saves command history to a file
 *@information: The parameter struct
 *
 *Description: Creates a file or appends to an existing file for command hitory
 *Return: 1 on success, else -1
 */
int write_history(info_t *information)
{
	ssize_t file_descriptor;
	char *file_name = get_history_filepath(information);
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
 *Function: build_history_list - Adds an entry to a history linked list
 *@information: Structure containing potential arguments. Used to maintain
 *@buf: Buffer
 *@line_count: The history line count, histcount
 *
 *Return: Always 0
 */
int build_history_list(info_t *information, char *buf, int line_count)
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
 *Function: read_history - Reads command history from file
 *@information: The parameter struct
 *
 *Description: Retrieves command history from a file
 *Return: histcount on success, 0 otherwise
 */
int read_history(info_t *information)
{
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_length, file_size = 0;
	struct stat file_status;
	char *buffer = NULL, *file_name = get_history_filepath(information);

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
			build_history_list(information, buffer + last, line_count++);
			last = i + 1;
		}
	}

	if (last != i)
		build_history_list(information, buffer + last, line_count++);
	free(buffer);
	information->histcount = line_count;
	while (information->histcount-- >= HIST_MAX)
		delete_node_at_index(&(information->history), 0);
	renumber_history(information);
	return (information->histcount);
}

/**
 *Function: get_history_filepath - Retrieves the history file path
 *@information: Parameter struct
 *
 *Description: Returns an allocated string containing the history file path
 *Return: Allocated string with the history file path
 */
char *get_history_filepath(info_t *information)
{
	char *history_path, *directory;

	directory = _getenv(information, "HOME=");
	if (!directory)
		return (NULL);
	history_path = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!history_path)
		return (NULL);
	history_path[0] = '\0';
	_strcpy(history_path, directory);
	_strcat(history_path, "/");
	_strcat(history_path, HIST_FILE);
	return (history_path);
}

/**
 *Function: renumber_history - Renumbers the history linked list after changes
 *@information: Structure containing potential arguments. Used to maintain
 *
 *Return: The new histcount
 */
int renumber_history(info_t *information)
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
