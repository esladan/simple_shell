#include "shell.h"


list__t *addNode(list__t **head, const char *str, int num)
{
	list__t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list__t));
	if (!new_head)
		return (NULL);
	_mem_set((void *)new_head, 0, sizeof(list__t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}


list__t *addNodeEnd(list__t **head, const char *str, int num)
{
	list__t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list__t));
	if (!new_node)
		return (NULL);
	_mem_set((void *)new_node, 0, sizeof(list__t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}


size_t printListStr(const list__t *h)
{
	size_t i = 0;

	while (h)
	{
		___puts(h->str ? h->str : "(nil)");
		___puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}


int deleteNodeAtIndex(list__t **head, unsigned int index)
{
	list__t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

void freeList(list__t **head_ptr)
{
	list__t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
