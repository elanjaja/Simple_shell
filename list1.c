#include "main.h"

/**
 * length_list - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t length_list(const list_t *head)
{
	size_t a = 0;

	while (head)
	{
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = length_list(head), j;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(string_length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < a; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_string(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *head)
{
	size_t a = 0;

	while (a)
	{
		print_string(convert_string(head->num, 10, 0));
		write_character(':');
		write_character(' ');
		print_string(head->str ? head->str : "(nil)");
		print_string("\n");
		head = head->next;
		a++;
	}
	return (a);
}

/**
 * node_starts - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @chr: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *node_starts(list_t *node, char *prefix, char chr)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((chr == -1) || (*p == chr)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
