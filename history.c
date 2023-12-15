#include "main.h"

/**
 * history_file - gets the history file path
 * @data: parameter struct
 *
 * Return: allocated string containg history file path
 */

char *history_file(data_t *data)
{
	char *buf, *dir;

	dir = get_environ(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string_length(dir) + string_length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_string(buf, dir);
	_catstr(buf, "/");
	_catstr(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - Writes command history to a file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(data_t *data)
{
	ssize_t fd;
	char *filename = history_file(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads command history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(data_t *data)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = history_file(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history(data, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		delete_node_index(&(data->history), 0);
	renumber_history(data);
	return (data->histcount);
}

/**
 * build_history - adds entry to a history linked
 * @data: framework containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always return 0
 */
int build_history(data_t *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_at_end(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @data: framework  containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(data_t *data)
{
	list_t *node = data->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (data->histcount = a);
}
