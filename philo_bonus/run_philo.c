#include "philo.h"

void	print_what_philo_do(unsigned long time, int id, char *str,
	 t_g_strukt *data)
{
	sem_wait(data->print);
	printf("%lu	%d	%s", time, id, str);
	sem_post(data->print);
}

void	take_forks(int id, t_g_strukt *data)
{
	sem_wait(data->forks);
	print_what_philo_do(get_time(data->start_time), id + 1, "has taken a fork\n",
		 data);
	sem_wait(data->forks);
	print_what_philo_do(get_time(data->start_time), id + 1, "has taken a fork\n",
		 data);
}

void	philo_is_dying(t_g_strukt *data)
{
	print_what_philo_do(get_time(data->start_time), 1, "has taken a fork\n",
		 data);
	usleep(data->time_to_die);
}

void	cycle_of_philo_life(t_philos **p, unsigned long time, t_g_strukt *data)
{
	take_forks((*p)->id - 1, data);
	(*p)->status = 1;
	time = get_time(data->start_time);
	print_what_philo_do(get_time(data->start_time), (*p)->id, "is eating\n",
		 data);
	ft_usleep(get_time(data->start_time), data->time_to_eat, data);
	(*p)->last_eat = get_time(data->start_time);
	(*p)->status = 0;
	sem_post(data->forks);
	sem_post(data->forks);
	print_what_philo_do(get_time(data->start_time), (*p)->id, "is sleeping\n",
		 data);
	(*p)->eat_times++;
	ft_usleep(get_time(data->start_time), data->time_to_sleep, data);
	print_what_philo_do(get_time(data->start_time), (*p)->id, "is thinking\n",
		 data);
}

void	*run_philo(void *arg)
{
	t_philos		*p;
	unsigned long	time;
	t_g_strukt		*data;

	p = (t_philos *)arg;
	data = (t_g_strukt *)p->data;
	time = 0;
	if (data->nmbr_of_philosophers == 1)
		philo_is_dying(data);
	else
	{
		while (TRUE)
			cycle_of_philo_life(&p, time, data);
	}
	return (NULL);
}
