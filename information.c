#include "shell.h"

/**
 * set_info - Initializes the info_t the argument vector.
 * @info_struct: Pointer to the info_t struct.
 * @arg_vector: Argument vector (av).
 */
void set_info(info_t *info_struct, char **arg_vector)
{
	int l = 0;

	info_struct->fname = arg_vector[0];
	if (info_struct->arg)
	{
		info_struct->argv = strtow(info_struct->arg, " \t");
		if (!info_struct->argv)
		{

			info_struct->argv = malloc(sizeof(char *) * 2);
			if (info_struct->argv)
			{
				info_struct->argv[0] = _strdup(info_struct->arg);
				info_struct->argv[1] = NULL;
			}
		}
		for (l = 0; info_struct->argv && info_struct->argv[l]; l++)
			;
		info_struct->argc = l;

		replace_alias(info_struct);
		replace_vars(info_struct);
	}
}

/**
 * clear_info - Initializes of info_t struct to NULL or 0.
 * @info_struct: Pointer to the info_t struct to be cleared.
 */
void clear_info(info_t *info_struct)
{
	info_struct->arg = NULL;
	info_struct->argv = NULL;
	info_struct->path = NULL;
	info_struct->argc = 0;
}

/**
 * free_info - Frees specific fields in the info_t struct.
 *  @info_struct: Pointer to the info_t struct.
 * @all: true if freeing all fields
 */
void free_info(info_t *info_struct, int all)
{
	ffree(info_struct->argv);
	info_struct->argv = NULL;
	info_struct->path = NULL;
	if (all)
	{
		if (!info_struct->cmd_buf)
			free(info_struct->arg);
		if (info_struct->env)
			free_list(&(info_struct->env));
		if (info_struct->history)
			free_list(&(info_struct->history));
		if (info_struct->alias)
			free_list(&(info_struct->alias));
		ffree(info_struct->environ);
			info_struct->environ = NULL;
		bfree((void **)info_struct->cmd_buf);
		if (info_struct->readfd > 2)
			close(info_struct->readfd);
		_putchar(BUF_FLUSH);
	}
}
