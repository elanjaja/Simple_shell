#include "main.h"

/**
 * string_length - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */
int string_length(char *str)
{
	int a = 0;

	if (!str)
		return (0);

	while (*str++)
		a++;
	return (a);
}

/**
 * string_compare - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_compare(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _catstr - concatenates two strings
 * @dest: the destination buffer
 * @source: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_catstr(char *dest, char *source)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*source)
		*dest++ = *source++;
	*dest = *source;
	return (ret);
}
