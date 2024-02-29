#include "shell.h"


int myexit(info__t *info)
{
	int exitcheck;

	if (info->argv[1])  
	{
		exitcheck = _erroAtoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_e__puts(info->argv[1]);
			_eput_char('\n');
			return (1);
		}
		info->err_num = _erroAtoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}


int mycd(info__t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		___puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getENV(info, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = getENV(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!getENV(info, "OLDPWD="))
		{
			___puts(s);
			_put_char('\n');
			return (1);
		}
		___puts(getENV(info, "OLDPWD=")), _put_char('\n');
		chdir_ret = 
			chdir((dir = getENV(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_e__puts(info->argv[1]), _eput_char('\n');
	}
	else
	{
		setENV(info, "OLDPWD", getENV(info, "PWD="));
		setENV(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}


int myhelp(info__t *info)
{
	char **arg_array;

	arg_array = info->argv;
	___puts("help call works. Function not yet implemented \n");
	if (0)
		___puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
