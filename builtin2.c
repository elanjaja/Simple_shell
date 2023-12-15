#include "main.h"

/**
 * display_history - displays the history list, one command by line, preceded
 *  with line numbers, starting at 0.
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 *  Return: Always return 0
 */
int display_history(data_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * alias_unset - removes alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_unset(data_t *data, char *str)
{
	char *ptr, c;
	int result;

	ptr = str_chr(str, '=');
	if (!ptr)
		return (1);
	c = *ptr;
	*ptr = 0;
	result = delete_node_index(&(data->alias),
		node_index(data->alias, node_starts(data->alias, str, -1)));
	*ptr = c;
	return (result);
}

/**
 * alias_set - sets alias to a string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_set(data_t *data, char *str)
{
	char *ptr;

	ptr = str_chr(str, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (alias_unset(data, str));

	alias_unset(data, str);
	return (add_node_at_end(&(data->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always return 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *a = NULL;

	if (node)
	{
		ptr = str_chr(node->str, '=');
		for (a = node->str; a <= ptr; a++)
			write_character(*a);
		write_character('\'');
		print_string(ptr + 1);
		print_string("'\n");
		return (0);
	}
	return (1);
}

/**
 * manage_alias - manages aliases, mimicking the alias builtin (man alias)
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 *  Return: Always return 0
 */
int manage_alias(data_t *data)
{
	int a = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; data->argv[a]; a++)
	{
		ptr = str_chr(data->argv[a], '=');
		if (ptr)
			alias_set(data, data->argv[a]);
		else
			print_alias(node_starts(data->alias, data->argv[a], '='));
	}

	return (0);
}
