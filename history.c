#include "shell.h"



char *getHistoryFile(info__t *info)
{
	char *buf, *dir;

	dir = getENV(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


int writeHistory(info__t *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list__t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		___putSfd(node->str, fd);
		_putfD('\n', fd);
	}
	_putfD(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

int readHistory(info__t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			buildListoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		buildListoryList(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	reNumberHistory(info);
	return (info->histcount);
}


int buildListoryList(info__t *info, char *buf, int linecount)
{
	list__t *node = NULL;

	if (info->history)
		node = info->history;
	addNodeEnd(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}


int reNumberHistory(info__t *info)
{
	list__t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
