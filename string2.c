#include "main.h"

/**
 * copy_string - copies a string from source to destination
 * @dest: the destination string
 * @source: the source string
 *
 * Return: pointer to destination
 */
char *copy_string(char *dest, char *source)
{
	int a = 0;

	if (dest == source || source == 0)
		return (dest);
	while (source[a])
	{
		dest[a] = source[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *print_string - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		write_character(str[a]);
		a++;
	}
}

/**
 * write_character - writes the character chr to stdout
 * @chr: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_character(char chr)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (chr == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (chr != BUF_FLUSH)
		buf[a++] = chr;
	return (1);
}
