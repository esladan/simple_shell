#include "shell.h"


int myENV(info__t *info)
{
	printListStr(info->env);
	return (0);
}


char *getENV(info__t *info, const char *name)
{
	list__t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}


int mySetENV(info__t *info)
{
	if (info->argc != 3)
	{
		_e__puts("Incorrect number of arguements\n");
		return (1);
	}
	if (setENV(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}


int myUnSetENV(info__t *info)
{
	int i;

	if (info->argc == 1)
	{
		_e__puts("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unSetENV(info, info->argv[i]);

	return (0);
}


int populateENVList(info__t *info)
{
	list__t *node = NULL;
	size_t i;

	for (i = 0; Environ[i]; i++)
		addNodeEnd(&node, Environ[i], 0);
	info->env = node;
	return (0);
}
