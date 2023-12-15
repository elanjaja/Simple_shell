#include "main.h"

/**
 * print_env - prints the current environment
 * @data: A framework that holds possible parameters,
 * utilized to uphold consistent function format.
 * constant function format.
 * Return: Always return 0
 */
int print_env(data_t *data)
{
	print_list_string(data->env);
	return (0);
}

/**
 * get_environ - gets the value of an environ variable
 * @data: structure containing potential arguments. Used to maintain
 * @name: environment variable
 * Return: the value of the environment variable.
 */
char *get_environ(data_t *data, const char *name)
{
	/* Access members using -> operator if data is a pointer */
	list_t *node = (data->env);
	/* Rest of the function logic */
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Create a new environment variable or
 *  make changes to an existing one
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 *  Return: Always return 0
 */
int my_setenv(data_t *data)
{
	if (data->argc != 3)
	{
		error_puts("wrong number of arguements\n");
		return (1);
	}
	if (set_env(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Removes an environment variable
 * @data: A framework that holds possible parameters,
 * utilized to uphold consistent function format.
 *  Return: Always return 0
 */
int my_unsetenv(data_t *data)
{
	int a;

	if (data->argc == 1)
	{
		error_puts("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= data->argc; a++)
		unset_env(data, data->argv[a]);

	return (0);
}

/**
 * populate_env - populates environment linked list
 * @data: A framework that holds possible parameters,
 * utilized to uphold consistent function format.
 * Return: Always return 0
 */
int populate_env(data_t *data)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_at_end(&node, environ[a], 0);
	data->env = node;
	return (0);
}
