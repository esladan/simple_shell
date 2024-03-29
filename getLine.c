#include "shell.h"


ssize_t input_buf(info__t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_handler);
#if USEgetLine
		r = getline(buf, &len_p, stdin);
#else
		r = getLine(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			info->linecount_flag = 1;
			removeComments(*buf);
			buildListoryList(info, *buf, info->histcount++);
			
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}


ssize_t getInput(info__t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_put_char(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len)	
	{
		j = i; 
		p = buf + i; 

		checkChain(info, buf, &j, i, len);
		while (j < len) 
		{
			if (isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len) 
		{
			i = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p)); 
	}

	*buf_p = buf; 
	return (r);
}


ssize_t read_buf(info__t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}


int getLine(info__t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _str_chr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _reallocs(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_strn_cat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}


void sigint_handler(__attribute__((unused))int sig_num)
{
	___puts("\n");
	___puts("$ ");
	_put_char(BUF_FLUSH);
}
