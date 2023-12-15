#include "main.h"

/**
 * **split_string - splits a string into words based delimiters
 * Repeated delimiters are ignored.
 * @str: the input string
 * @delim: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **split_string(char *str, char *delim)
{
	int a, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (a = 0; str[a] != '\0'; a++)
		if
			(!delimeter(str[a], delim) && (delimeter(str[a + 1], delim) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < numwords; j++)
	{
		while (delimeter(str[a], delim))
			a++;
		k = 0;
		while (!delimeter(str[a + k], delim) && str[a + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **split_string_alt - splits a string into words using a
 * single delimiter character.
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **split_string_alt(char *str, char delim)
{
	int a, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != delim && str[a + 1] == delim) ||
		    (str[a] != delim && !str[a + 1]) || str[a + 1] == delim)
			numwords++;
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, j = 0; j < numwords; j++)
	{
		while (str[a] == delim && str[a] != delim)
			a++;
		k = 0;
		while (str[a + k] != delim && str[a + k] && str[a + k] != delim)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[a++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
