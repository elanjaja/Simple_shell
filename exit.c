#include "main.h"

/**
 **_cpystr - copies a string up to a specified length
 *@dest: the destination string to be copied to
 *@source: the source string
 *@num: the number of characters to be copied
 *Return: the concatenated string
 */
char *_cpystr(char *dest, char *source, int num)
{
	int a, j;
	char *s = dest;

	a = 0;
	while (source[a] != '\0' && a < num - 1)
	{
		dest[a] = source[a];
		a++;
	}
	if (a < num)
	{
		j = a;
		while (j < num)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings up to a specified length
 * @dest: the first string
 * @source: the second string to append
 * @num: the maximum number of characters to concatenate
 * Return: pointer to the concatenated string
 */
char *_strncat(char *dest, char *source, int num)
{
	int a, j;
	char *s = dest;

	a = 0;
	j = 0;
	while (dest[a] != '\0')
		a++;
	while (source[j] != '\0' && j < num)
	{
		dest[a] = source[j];
		a++;
		j++;
	}
	if (j < num)
		dest[a] = '\0';
	return (s);
}

/**
 **str_chr - locates a character in a string
 *@str: the string to be parsed
 *@chr: the character to look for
 *Return:  pointer to the first occurrence of the character in the string
 */
char *str_chr(char *str, char chr)
{
	do {
		if (*str == chr)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
