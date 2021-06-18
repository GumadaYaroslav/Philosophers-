#include "philo.h"

void	print_what_philo_do(unsigned long time, int id, char *str,
	t_g_strukt *data)
{
	pthread_mutex_lock(&data->print);
	printf("%lu	%d	%s", time, id, str);
	pthread_mutex_unlock(&data->print);
}

void	take_forks(int l, int id, t_g_strukt *data)
{
	pthread_mutex_lock(&data->philos[id].priority);
	if (id % 2 == 1)
	{
		pthread_mutex_lock(&data->philos[id].fork);
		print_what_philo_do(get_time(data->start_time), id + 1,
			"has taken a fork\n", data);
		pthread_mutex_lock(&data->philos[l].fork);
		print_what_philo_do(get_time(data->start_time), id + 1,
			"has taken a fork\n", data);
	}
	else
	{
		pthread_mutex_lock(&data->philos[l].fork);
		print_what_philo_do(get_time(data->start_time), id + 1,
			"has taken a fork\n", data);
		pthread_mutex_lock(&data->philos[id].fork);
		print_what_philo_do(get_time(data->start_time), id + 1,
			"has taken a fork\n", data);
	}
	if (id + 1 == data->nmbr_of_philosophers)
		pthread_mutex_unlock(&data->philos[0].priority);
	else
		pthread_mutex_unlock(&data->philos[id + 1].priority);
}

void	philo_is_dying(t_g_strukt *data)
{
	pthread_mutex_lock(&data->philos[0].fork);
	print_what_philo_do(get_time(data->start_time), 1, "has taken a fork\n",
		 data);
	usleep(data->time_to_die);
}

void	cycle_of_philo_life(int left_fork, t_philos **p, unsigned long time,
	t_g_strukt *data)
{
	take_forks(left_fork, (*p)->id - 1, data);
	(*p)->status = 1;
	time = get_time(data->start_time);
	print_what_philo_do(time, (*p)->id, "is eating\n", data);
	usleep(data->time_to_eat * 1000);
	(*p)->last_eat = get_time(data->start_time);
	(*p)->status = 0;
	pthread_mutex_unlock(&(*p)->fork);
	pthread_mutex_unlock(&data->philos[left_fork].fork);
	print_what_philo_do(get_time(data->start_time), (*p)->id, "is sleeping\n",
		 data);
	(*p)->eat_times++;
	usleep(data->time_to_sleep * 1000);
	print_what_philo_do(get_time(data->start_time), (*p)->id, "is thinking\n",
		 data);
}

void	*run_philo(void *arg)
{
	t_philos		*p;
	int				left_fork;
	unsigned long	time;
	t_g_strukt		*data;

	p = (t_philos *)arg;
	data = (t_g_strukt *)p->data;
	time = 0;
	if (p->id == 0)
		left_fork = data->nmbr_of_philosophers - 1;
	else
		left_fork = p->id - 2;
	if (data->nmbr_of_philosophers == 1)
		philo_is_dying(data);
	else
	{
		while (TRUE)
			cycle_of_philo_life(left_fork, &p, time, data);
	}
	return (NULL);
}
