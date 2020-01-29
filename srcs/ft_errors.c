#include "../includes/cubd.h"

int     check_args(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc > 3 && (i = 1))
		ft_printf_fd(2, "Trop d'arguments\n");
	else if (argc == 3 && ft_strcmp(argv[2], "-save") != 0 && (i = 1))
		ft_printf_fd(2, "Option '%s' inconnue\n", argv[2]);
	else if (argc < 2 && (i = 1))
		ft_printf_fd(2, "Pas assez d'arguments\n");
	if (i == 1)
		return (-1);
	i = ft_strlen(argv[1]) - 1;
	if (i < 4 || (argv[1][i] != 'b' || argv[1][i - 1] != 'u' || 
					argv[1][i - 2] != 'c' || argv[1][i - 3] != '.'))
	{
		ft_printf_fd(2, "Veuillez entrer un fichier au format  \"*.cub\"\n");
		return (-1);
	}
	return (1);
}

int     ft_errors(int err)
{
    ft_printf_fd(2, "Error\n");
    if (err == 1)
        ft_printf_fd(2, "No such file or directory\n");
    if (err == 2)
        ft_printf_fd(2, "Error reading file\n");
    exit(1);
    return (1);
}

