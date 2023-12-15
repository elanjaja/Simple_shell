#include "main.h"

/**
 *environ_string - returns the string array copy of our environ
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 * Return: Always return 0
 */
char **environ_string(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * unset_env - Remove an environment variable
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 * @var: The string representing the environment variable to be removed
 * Return: 1 on deletion, 0 otherwise
 */
int unset_env(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t a = 0;
	char *ptr;

	if (!node || !var)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			data->env_changed = delete_node_index(&(data->env), a);
			a = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (data->env_changed);
}

/**
 * set_env - Initialize a new environment variable,
 *  or modify an existing one
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 * @var: The string representing the environment variable name
 * @value: The string representing the environment variable value
 *  Return: Always return 0
 */
int set_env(data_t *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *ptr;

	if (!var || !value)
		return (0);

	buf = malloc(string_length(var) + string_length(value) + 2);
	if (!buf)
		return (1);
	copy_string(buf, var);
	_catstr(buf, "=");
	_catstr(buf, value);
	node = data->env;
	while (node)
	{
		ptr = starts_with(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_at_end(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}
