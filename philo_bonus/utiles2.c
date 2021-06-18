#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t number, size_t size)
{
	void	*s;

	if (number == (size_t)0 || size == (size_t)0)
	{
		number = (size_t)1;
		size = (size_t)1;
	}
	s = malloc(number * size);
	if (s == NULL)
		return (NULL);
	else
		s = ft_bzero(s, number * size);
	return (s);
}

unsigned long	get_time(unsigned long start_time)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000 + time.tv_usec / 1000) - start_time);
}

int	is_int(char *num)
{
	int	flag;

	flag = 0;
	if (num && num[0] == '-')
		flag = 1;
	if (flag)
	{
		if (ft_strlen(num) > 11)
			return (FALSE);
	}
	else
	{
		if (ft_strlen(num) > 10)
			return (FALSE);
	}
	if (-2147483648 > ft_atoi(num) || ft_atoi(num) > 2147483647)
		return (FALSE);
	return (TRUE);
}

void	ft_usleep(unsigned long start, int sleep_time, t_g_strukt *data)
{
	while (get_time(data->start_time) - start < (unsigned long)sleep_time)
		usleep(100);
}
