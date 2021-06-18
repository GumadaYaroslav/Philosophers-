#include "philo.h"

void	create_philo(t_philos *philo, int i, t_g_strukt *data)
{
	philo->id = i;
	philo->eat_times = 0;
	philo->data = (void *)data;
}

void	pars_param(int argc, char **argv, t_g_strukt *data)
{
	data->nmbr_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
}

void	craate_sem(t_g_strukt *data)
{
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("lock");
	data->forks = sem_open("forks", O_CREAT, S_IRWXU,
			data->nmbr_of_philosophers);
	if (data->forks == (sem_t *)-1)
		error("sem error");
	data->priority = sem_open("priority", O_CREAT, S_IRWXU, 1);
	if (data->priority == (sem_t *)-1)
		error ("sem error");
	data->print = sem_open("print", O_CREAT, S_IRWXU, 1);
	if (data->priority == (sem_t *)-1)
		error ("sem error");
}

int	pars(int argc, char **argv, t_g_strukt *data)
{
	int	i;

	data->start_time = 0;
	if (validation(argc, argv) == FALSE)
		return (FALSE);
	i = 0;
	pars_param(argc, argv, data);
	craate_sem(data);
	data->philos = ft_calloc(data->nmbr_of_philosophers,
			sizeof(t_philos));
	if (!data->philos)
	{
		error("malloc error");
		return (FALSE);
	}
	while (i++ != data->nmbr_of_philosophers)
		create_philo(&data->philos[i - 1], i, data);
	data->start_time = get_time(data->start_time);
	return (TRUE);
}
