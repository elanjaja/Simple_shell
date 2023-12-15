#include "main.h"

/**
 * executable - determines if a file is an executable command
 * @data: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int executable(data_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * copy_chars - copies characters from start to stop index
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *copy_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int a = 0, k = 0;

	for (k = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buf[k++] = pathstr[a];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - finds the command in the PATH string
 * @data: the data struct
 * @pathstr: the PATH string
 * @command: the command to find
 *
 * Return: full path of command if found or NULL
 */
char *find_path(data_t *data, char *pathstr, char *command)
{
	int a = 0, current_position = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_length(command) > 2) && starts_with(command, "./"))
	{
		if (executable(data, command))
			return (command);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			path = copy_chars(pathstr, current_position, a);
			if (!*path)
				_catstr(path, command);
			else
			{
				_catstr(path, "/");
				_catstr(path, command);
			}
			if (executable(data, path))
				return (path);
			if (!pathstr[a])
				break;
			current_position = a;
		}
		a++;
	}
	return (NULL);
}
