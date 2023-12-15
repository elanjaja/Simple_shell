#include "main.h"

/**
 * shell_exit - exits the shell
 * @data:  A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 *  Return: exits with a given exit status
 *         (0) if data.argv[0] != "exit"
 */
int shell_exit(data_t *data)
{
	int exitcode;

	if (data->argv[1]) /* If there should be an exit arguement */
	{
		exitcode = _erratoi(data->argv[1]);
		if (exitcode == -1)
		{
			data->status = 2;
			print_error(data, "Illegal number: ");
			print_string(data->argv[1]);
			write_character('\n');
			return (1);
		}
		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process
 * @data: A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 *  Return: Always return 0
 */
int my_cd(data_t *data)
{
	char *a, *dir, buffer[1024];
	int chdir_result;

	a = getcwd(buffer, 1024);
	if (!a)
		print_string("Error: Failed to get current directory\n");
	if (!data->argv[1])
	{
		dir = get_environ(data, "HOME=");
		if (!dir)
			chdir_result =
				chdir((dir = get_environ(data, "PWD=")) ? dir : "/");
		else
			chdir_result = chdir(dir);
	}
	else if (string_compare(data->argv[1], "-") == 0)
	{
		if (!get_environ(data, "OLDPWD="))
		{
			print_string(a);
			write_character('\n');
			return (1);
		}
		print_string(get_environ(data, "OLDPWD=")), write_character('\n');
		chdir_result =
			chdir((dir = get_environ(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_result = chdir(data->argv[1]);
	if (chdir_result == -1)
	{
		print_error(data, "can't cd to ");
		error_puts(data->argv[1]), error_putchar('\n');
	}
	else
	{
		set_env(data, "OLDPWD", get_environ(data, "PWD="));
		set_env(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - changes the current directory of the process
 * @data:  A framework that holds possible parameters,
 *  utilized to uphold consistent function format.
 *  Return: Always return 0
 */
int my_help(data_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	print_string("Help command called. Functionality not implemented yet.\n");
	if (0)
		print_string(*arg_array); /* temporary unused variable workaround */
	return (0);
}
