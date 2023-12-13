#include "shell.h"

/**
 * dup_chars -Duplicates characters from a string within.
 * @path_string:  The original string containing .
 * @start_index: Starting index from which to duplicate.
 * @stop_index: Stopping index until which characters.
 *
 * Return: Pointer to a new buffer containing duplicated characters
 */
char *dup_chars(char *path_string, int start_index, int stop_index)
{
	static char buf[1024];
	int l = 0, j = 0;

	for (j = 0, l = start_index; l < stop_index; l++)
		if (path_string[l] != ':')
			buf[j++] = path_string[l];
	buf[j] = 0;
	return (buf);
}

/**
 * find_path -Finds the specified command in the PATH string.
 * @info_struct: Pointer to the info struct.
 * @path_string: The PATH string.
 * @command: the cmd to find
 *
 * Pointer to the full path of the command if found, otherwise NULL.
 * Return: the file path
 */
char *find_path(info_t *info_struct, char *path_string, char *command)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (is_cmd(info_struct, command))
			return (command);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = dup_chars(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (is_cmd(info_struct, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * is_cmd - Checks if a file is an executable command.
 * @information: Pointer to the info struct.
 * @file_path: path to the file
 *
 * Return: 1 if the file is an executable command, 0 otherwise.
 */
int is_cmd(info_t *information, char *file_path)
{
	struct stat st;

	(void)information;
	if (!file_path || stat(file_path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
