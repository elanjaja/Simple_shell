#include "main.h"

/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *str)
{
	int a = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* This step skips the leading '+' character, if present */
	for (a = 0;  str[a] != '\0'; a++)
	{
		if (str[a] >= '0' && str[a] <= '9')
		{
			result *= 10;
			result += (str[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @data: the parameter & return data struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(data_t *data, char *estr)
{
	error_puts(data->fname);
	error_puts(": ");
	print_decimal(data->linecount, STDERR_FILENO);
	error_puts(": ");
	error_puts(data->argv[0]);
	error_puts(": ");
	error_puts(estr);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input integer to print
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int print_decimal(int input, int fd)
{
	int (*write_character)(char) = write_character;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		write_character = error_putchar;
	if (input < 0)
	{
		_abs_ = -input;
		write_character('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			write_character('0' + current / a);
			count++;
		}
		current %= a;
	}
	write_character('0' + current);
	count++;

	return (count);
}

/**
 * convert_string - converts a number to a string representation
 * @num: number to covert
 * @base: base for conversion
 * @flags: argument flags
 *
 * Return: string representation of the number
 */
char *convert_string(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * replace_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always return0;
 */
void replace_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
