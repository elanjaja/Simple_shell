#include "main.h"

/**
 * shell_loop - main shell loop
 * @data: the parameter and return data struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell_loop(data_t *data, char **av)
{
	ssize_t rs = 0;
	int builtin_return = 0;

	while (rs != -1 && builtin_return != -2)
	{
		clear_data(data);
		if (!interactive_mood(data))
			print_string("$ ");
		error_putchar(BUF_FLUSH);
		rs = get_input(data);
		if (rs != -1)
		{
			set_data(data, av);
			builtin_return = find_builtin_command(data);
			if (builtin_return == -1)
				find_cmd(data);
		}
		else if (!interactive_mood(data))
			write_character('\n');
		free_data(data, 0);
	}
	write_history(data);
	free_data(data, 1);
	if (!interactive_mood(data) && data->status)
		exit(data->status);
	if (builtin_return == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin_command - finds a builtin command
 * @data: the parameter and return data struct
 *
 * Return: -1 if builtin not found,
 *	0 if builtin executed successfully,
 *	1 if builtin found but not successful,
 *	-2 if builtin signals exit()
 */
int find_builtin_command(data_t *data)
{
	int a, built_in_return = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", print_env},
		{"help", my_help},
		{"history", display_history},
		{"setenv", my_setenv},
		{"unsetenv", _myunsetenv},
		{"cd", my_cd},
		{"alias", manage_alias},
		{NULL, NULL}
	};

	for (a = 0; builtintbl[a].type; a++)
		if (string_compare(data->argv[0], builtintbl[a].type) == 0)
		{
			data->linecount++;
			built_in_return = builtintbl[a] .func(data);
			break;
		}
	return (built_in_return);
}

/**
 * find_cmd - finds a command in PATH
 * @data: the parameter and return data struct
 *
 * Return: void
 */
void find_cmd(data_t *data)
{
	char *path = NULL;
	int a, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->linecount++;
		data->linecount_flag = 0;
	}
	for (a = 0, k = 0; data->arg[a]; a++)
		if (!delimeter(data->arg[a], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(data, get_environ(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		execute_command(data);
	}
	else
	{
		if ((interactive_mood(data) || get_environ(data, "PATH=")
			|| data->argv[0][0] == '/') && executable(data, data->argv[0]))
			execute_command(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			print_error(data, "not found\n");
		}
	}
}

/**
 * execute_command - forks an execute thread to run command
 * @data: the parameter and return data struct
 *
 * Return: void
 */
void execute_command(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, environ_string(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				print_error(data, "Permission denied\n");
		}
	}
}
