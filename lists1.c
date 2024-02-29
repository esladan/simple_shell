#include "shell.h"


size_t listLen(const list__t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

char **listToStrings(list__t *head)
{
	list__t *node = head;
	size_t i = listLen(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}



size_t printList(const list__t *h)
{
	size_t i = 0;

	while (h)
	{
		___puts(convertNumber(h->num, 10, 0));
		_put_char(':');
		_put_char(' ');
		___puts(h->str ? h->str : "(nil)");
		___puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}


list__t *nodeStartsWith(list__t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


ssize_t getNodeIndex(list__t *head, list__t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
