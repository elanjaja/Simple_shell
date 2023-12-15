#include "main.h"

/**
 **_memset - fills memory with a constant byte
 *@dest: the pointer to the memory area
 *@byte: the byte to fill *dest with
 *@num: the amount of bytes to be filled
 *Return: (dest) a pointer to the memory area s
 */
char *_memset(char *dest, char byte, unsigned int num)
{
	unsigned int a;

	for (a = 0; a < num; a++)
		dest[a] = byte;
	return (dest);
}

/**
 * free_string - frees memory allocated to a string array
 * @as: array of strings
 */
void free_string(char **as)
{
	char **a = as;

	if (!as)
		return;
	while (*as)
		free(*as++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
