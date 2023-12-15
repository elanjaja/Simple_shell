#include "main.h"

/**
 * chain_delimeter - test if current character in buffer is a chain delimeter
 * @data: the parameter struct
 * @buf: the character buffer
 * @pos: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int chain_delimeter(data_t *data, char *buf, size_t *pos)
{
	size_t k = *pos;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found end of this command */
	{
		buf[k] = 0; /* replace semicolon with null */
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = k;
	return (1);
}

/**
 * checkchain - checks we should continue chaining based on last status
 * @data: the parameter struct
 * @buf: the char buffer
 * @pos: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checkchain(data_t *data, char *buf, size_t *pos, size_t i, size_t len)
{
	size_t k = *pos;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*pos = k;
}

/**
 * restore_alias - restores an aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int restore_alias(data_t *data)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = str_chr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * restore_vars - restores vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int restore_vars(data_t *data)
{
	int a = 0;
	list_t *node;

	for (a = 0; data->argv[a]; a++)
	{
		if (data->argv[a][0] != '$' || !data->argv[a][1])
			continue;

		if (!string_compare(data->argv[a], "$?"))
		{
			replace_string(&(data->argv[a]),
				_strdup(convert_string(data->status, 10, 0)));
			continue;
		}
		if (!string_compare(data->argv[a], "$$"))
		{
			replace_string(&(data->argv[a]),
				_strdup(convert_string(getpid(), 10, 0)));
			continue;
		}
		node = node_starts(data->env, &data->argv[a][1], '=');
		if (node)
		{
			replace_string(&(data->argv[a]),
				_strdup(str_chr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
