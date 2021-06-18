#include "philo.h"
#include <stdlib.h>
#include <stdio.h>

static long long	ft_return_num(char *str, int flag)
{
	int			i;
	long long	num;

	num = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if (flag == 1)
		return (num * (-1));
	return (num);
}

long	ft_atoi(const char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (str[i] == '\f' || str[i] == '\n' || str[i] == '\r' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == ' ')
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			flag = 1;
		i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
		return ((long)ft_return_num((char *)&str[i], flag));
	return (0);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	error(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	*ft_bzero(void *s, size_t len)
{
	int		i;
	char	*buf;

	buf = (char *)s;
	i = 0;
	while (i < (int)len)
	{
		buf[i] = 0;
		i++;
	}
	return (s);
}
