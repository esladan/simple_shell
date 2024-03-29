#include "shell.h"


int main(int ac, char **av)
{
	info__t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_e__puts(av[0]);
				_e__puts(": 0: Can't open ");
				_e__puts(av[1]);
				_eput_char('\n');
				_eput_char(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populateENVList(info);
	readHistory(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
