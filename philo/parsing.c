#include "philo.h"

void	create_philo(t_philos *philo, int i, t_g_strukt *data)
{
	philo->id = i;
	philo->eat_times = 0;
	philo->data = (void *)data;
	pthread_mutex_init(&philo->priority, NULL);
	pthread_mutex_init(&philo->fork, NULL);
}

int	pars(int argc, char **argv, t_g_strukt *data)
{
	int	i;

	if (validation(argc, argv) == FALSE)
		return (FALSE);
	data->nmbr_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	i = 0;
	data->philos = ft_calloc(data->nmbr_of_philosophers,
			sizeof(t_philos));
	if (!data->philos)
	{
		error("malloc error");
		return (FALSE);
	}
	while (i++ != data->nmbr_of_philosophers)
		create_philo(&data->philos[i - 1], i, data);
	pthread_mutex_init(&data->print, NULL);
	data->start_time = get_time(data->start_time);
	return (TRUE);
}
