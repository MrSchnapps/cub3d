#include "cub3d.h"

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
	fpf(2, "Error\n");
	(err == 1) ? fpf(2, "No such file or directory.\n") : 0;
	(err == 2) ? fpf(2, "Error reading file.\n"): 0;
	(err == 3) ? fpf(2, "Too much arguments.\n") : 0;
	(err == 4) ? fpf(2, "Unkown option.\n") : 0;
	(err == 5) ? fpf(2, "Not enough arguments.\n") : 0;
	(err == 6) ? fpf(2, "Enter a file in format \"*.cub\".\n") : 0;
	(err == 7) ? fpf(2, "Unkown information(s) in your map file.\n") : 0;
	(err == 8) ? fpf(2, "Error in resolution value.\n") : 0;
	(err == 9) ? fpf(2, "Error in floor color value.\n") : 0;
	(err == 10) ? fpf(2, "Error in ceil color value.\n") : 0;
	(err == 11) ? fpf(2, "Memory error.\n") : 0;
	(err == 12) ? fpf(2, "Missing map in map file.\n") : 0;
	(err == 13) ? fpf(2, "To few lines in your map.\n") : 0;
	(err == 14) ? fpf(2, "Wall missing in the map borders.\n") : 0;
	(err == 15) ? fpf(2, "Lines are not the same size or too small\n") : 0;
	(err == 16) ? fpf(2, "Too much start position in your map\n") : 0;
	(err == 17) ? fpf(2, "Unkown value in your map\n") : 0;
	(err == 18) ? fpf(2, "Missing start position\n") : 0;
	(err == 19) ? fpf(2, "You cannot have content under the map\n") : 0;
	exit(1);
	return (1);
}

