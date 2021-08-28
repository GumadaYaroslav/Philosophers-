#include "philo.h"

int	track_philo(unsigned long time, int i, int *flag, t_g_strukt *data)
{
	time = get_time(data->start_time);
	if (data->philos[i].eat_times < data->must_eat)
		*flag = FALSE;
	if (time > data->philos[i].last_eat && time - data->philos[i].last_eat
		> (unsigned long)data->time_to_die)
	{
		if (data->philos[i].status == FALSE)
		{
			pthread_mutex_lock(&data->print);
			printf("%lu	%d	%s", time, i + 1, "died\n");
			return (FALSE);
		}
	}
	return (TRUE);
}

int	tracking_philos(t_g_strukt *data)
{
	int				i;
	int				flag;
	unsigned long	time;

	i = -1;
	time = 0;
	while (TRUE)
	{
		i = 0;
		flag = TRUE;
		while (i < data->nmbr_of_philosophers)
		{
			if (track_philo(time, i, &flag, data) == FALSE)
				return (1);
			i++;
		}
		if (data->must_eat != -1 && flag == TRUE)
			return (2);
	}
}

void	run_philos(t_g_strukt *data)
{
	int	i;

	i = 0;
	while (i < data->nmbr_of_philosophers)
	{
		data->philos[i].last_eat = get_time(data->start_time);
		pthread_create(&data->philos[i].thread, NULL, run_philo,
			(void *)&data->philos[i]);
		i++;
	}
}

void	cleaning(t_g_strukt *data)
{
	int	i;

	i = -1;
	while (++i < data->nmbr_of_philosophers)
	{
		pthread_detach(data->philos[i].thread);
	}
	i = -1;
	while (++i < data->nmbr_of_philosophers)
	{
		pthread_mutex_destroy(&data->philos[i].priority);
		pthread_mutex_destroy(&data->philos[i].fork);
	}
	pthread_mutex_destroy(&data->print);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_g_strukt	data;

	if (pars(argc, argv, &data) == FALSE)
		return (1);
	run_philos(&data);
	tracking_philos(&data);
	cleaning(&data);
	return (0);
}
