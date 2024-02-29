#include "shell.h"


int _myHistory(info__t *info)
{
	printList(info->history);
	return (0);
}


int unset_alias(info__t *info, char *str)
{
	char *p, c;
	int ret;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, nodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}


int set_alias(info__t *info, char *str)
{
	char *p;

	p = _str_chr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (addNodeEnd(&(info->alias), str, 0) == NULL);
}


int print_alias(list__t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _str_chr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_put_char(*a);
		_put_char('\'');
		___puts(p + 1);
		___puts("'\n");
		return (0);
	}
	return (1);
}


int myAlias(info__t *info)
{
	int i = 0;
	char *p = NULL;
	list__t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _str_chr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(nodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
