#include "philo.h"

static int	check_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] < '0' || argv[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

int	validation(int argc, char **argv)
{
	if (argc < 5 | argc > 6)
	{
		error("invalid number of argument.");
		return (0);
	}
	while (argc - 1 != 0)
	{
		if (check_arg(argv[argc - 1]) == -1)
		{
			error("invalid argument.");
			return (0);
		}
		if (is_int(argv[argc - 1]) == FALSE)
			error("invalid argument.");
		argc--;
	}
	if (ft_atoi(argv[1]) == 0)
	{
		error("invalid number of philosophers.");
		return (0);
	}
	return (1);
}
