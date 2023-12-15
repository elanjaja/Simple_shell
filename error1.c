#include "main.h"

/**
 * error_puts - prints an input string toi standard error
 * @str: the string to be printed
 *
 * This function prints a string to the standard error output
 */
void error_puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		error_putchar(str[a]);
		a++;
	}
}

/**
 * error_putchar - writes the character c to standard error output
 * @chr: The character to print
 *
 * This function writes a character to the standard error output.
 * Return: On success, it returns 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int error_putchar(char chr)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (chr != BUF_FLUSH)
		buf[a++] = chr;
	return (1);
}

/**
 * _putfd - writes the character c to the given file descriptor
 * @chr: The character to print
 * @fd: The file descriptor to write to
 *
 * This function writes a character to the specified file descriptor.
 * Return: On success, it returns 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char chr, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (chr != BUF_FLUSH)
		buf[a++] = chr;
	return (1);
}

/**
 *_putsfd - prints an input string to the specified file descriptor
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (!str)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
