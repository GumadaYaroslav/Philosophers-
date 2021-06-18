#include "philo.h"

int	track_philo(t_philos *p, int *flag, t_g_strukt *data)
{
	unsigned long	time;

	time = get_time(data->start_time);
	if (p->eat_times < (long)data->must_eat)
	{
		*flag = FALSE;
	}
	if (time > p->last_eat && time - p->last_eat
		> (unsigned long)data->time_to_die)
	{
		sem_wait(data->print);
		printf("%lu	%d	%s", time, p->id, "died\n");
		return (FALSE);
	}
	return (TRUE);
}

void	*tracking_philos(void *arg)
{
	int				i;
	int				flag;
	t_philos		*p;
	t_g_strukt		*data;

	p = (t_philos *)arg;
	data = (t_g_strukt *)p->data;
	i = -1;
	while (TRUE)
	{
		flag = TRUE;
		if (track_philo(p, &flag, data) == FALSE)
		{
			exit(0);
			return (NULL);
		}
		ft_usleep(get_time(data->start_time), 1, data);
		if (data->must_eat != -1 && flag == TRUE)
		{
			exit(1);
			return (NULL);
		}
	}
	return (NULL);
}

void	go_philos(int i, t_g_strukt *data)
{
	pthread_t			wait;

	data->philos[i].last_eat = get_time(data->start_time);
	pthread_create(&data->philos[i].thread, NULL, run_philo,
		(void *)&data->philos[i]);
	pthread_detach(data->philos[i].thread);
	pthread_create(&wait, NULL, tracking_philos, (void *)&data->philos[i]);
	pthread_join(wait, NULL);
}

void	waiter(int i, t_g_strukt *data)
{
	int	ret;

	while (++i < data->nmbr_of_philosophers)
	{
		waitpid(-1, &ret, 0);
		if (WEXITSTATUS(ret) == 0)
		{
			i = 0;
			while (i < data->nmbr_of_philosophers)
			{
				kill(data->philos[i].pid, SIGKILL);
				i++;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	int			i;
	t_g_strukt	data;

	if (pars(argc, argv, &data) == FALSE)
		return (1);
	i = -1;
	while (++i < data.nmbr_of_philosophers)
	{
		data.philos[i].pid = fork();
		if (data.philos[i].pid == -1)
			error("error while creating subprocess");
		else if (data.philos[i].pid == 0)
			go_philos(i, &data);
	}
	i = -1;
	waiter(i, &data);
	return (0);
}
