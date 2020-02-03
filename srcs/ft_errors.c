#include "../includes/cubd.h"

int     check_args(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc > 3 && (i = 1))
		ft_errors(3);
	else if (argc == 3 && ft_strcmp(argv[2], "-save") != 0 && (i = 1))
		ft_errors(4);
	else if (argc < 2 && (i = 1))
		ft_errors(5);
	if (i == 1)
		return (-1);
	i = ft_strlen(argv[1]) - 1;
	if (i < 4 || (argv[1][i] != 'b' || argv[1][i - 1] != 'u' || 
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.'))
	{
		ft_errors(6);
		return (-1);
	}
	return (1);
}

int     ft_errors(int err)
{
	ft_printf_fd(2, "Error\n");
	if (err == 1)
		ft_printf_fd(2, "No such file or directory\n");
	else if (err == 2)
		ft_printf_fd(2, "Error reading file\n");
	else if (err == 3)
		ft_printf_fd(2, "Too much arguments\n");
	else if (err == 4)
		ft_printf_fd(2, "Unkown option\n");
	else if (err == 5)
		ft_printf_fd(2, "Not enough arguments\n");
	else if (err == 6)
		ft_printf_fd(2, "Please enter a file in format \"*.cub\"\n");
	else if (err == 7)
		ft_printf_fd(2, "Bad information in your map file\n");
	else if (err == 8)
		ft_printf_fd(2, "Error in resolution value\n");

	else if (err == 10)
		ft_printf_fd(2, "Memory error\n");
	exit(1);
	return (1);
}

