#include "main.h"

/**
 * main - Entry point of the custom shell program
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	data_t data[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				error_puts(av[0]);
				error_puts(": 0: Can't open ");
				error_puts(av[1]);
				error_putchar('\n');
				error_putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = fd;
	}
	populate_env(data);
	read_history(data);
	shell_loop(data, av);
	return (EXIT_SUCCESS);
}
