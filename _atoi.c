#include "main.h"

/**
 * interactive_mode - returns true if shell is interactive mode
 * @data: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive_mode(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * delimeter - checks if character is a delimeter
 * @chr: the character to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int delimeter(char chr, char *delim)
{
	while (*delim)
		if (*delim++ == chr)
			return (1);
	return (0);
}

/**
 *alphabetic - checks for alphabetic character
 *@chr: The character to check
 *Return: 1 if chr is alphabetic, 0 otherwise
 */

int alphabetic(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0;  str[a] != '\0' && flag != 2; a++)
	{
		if (str[a] == '-')
			sign *= -1;

		if (str[a] >= '0' && str[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
