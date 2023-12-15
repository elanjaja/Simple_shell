#include "main.h"

/**
 * clear_data - initializes data_t struct
 * @data: struct address
 */
void clear_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * set_data - initializes data_t struct
 * @data: struct address
 * @av: argument vector
 */
void set_data(data_t *data, char **av)
{
	int a = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = split_string(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _strdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (a = 0; data->argv && data->argv[a]; a++)
			;
		data->argc = a;

		restore_alias(data);
		restore_vars(data);
	}
}

/**
 * free_data - frees data_t struct fields
 * @data: struct address
 * @af: true if freeing all fields
 */
void free_data(data_t *data, int af)
{
	free_string(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (af)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list_node(&(data->env));
		if (data->history)
			free_list_node(&(data->history));
		if (data->alias)
			free_list_node(&(data->alias));
		free_string(data->environ);
			data->environ = NULL;
		bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		write_character(BUF_FLUSH);
	}
}
