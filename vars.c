#include "shell.h"


int isChain(info__t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') 
	{
		buf[j] = 0; 
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}


void checkChain(info__t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}


int replaceAlias(info__t *info)
{
	int i;
	list__t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _str_chr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}


int replaceVars(info__t *info)
{
	int i = 0;
	list__t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convertNumber(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaceString(&(info->argv[i]),
				_strdup(convertNumber(getpid(), 10, 0)));
			continue;
		}
		node = nodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaceString(&(info->argv[i]),
				_strdup(_str_chr(node->str, '=') + 1));
			continue;
		}
		replaceString(&info->argv[i], _strdup(""));

	}
	return (0);
}


int replaceString(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
