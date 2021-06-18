#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <stdio.h>
# define TRUE 1
# define FALSE 0

typedef struct s_philos
{
	int					id;
	unsigned long		last_eat;
	long				eat_times;
	int					status;
	pthread_t			thread;
	pid_t				pid;
	void				*data;
}					t_philos;

typedef struct s_g_strukt
{
	int				nmbr_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*priority;
	time_t			start_time;
	t_philos		*philos;
}				t_g_strukt;

int				ft_strlen(char *s);
void			error(char *str);
long			ft_atoi(const char *str);
int				validation(int argc, char **argv);
int				pars(int argc, char **argv, t_g_strukt *data);
void			*ft_calloc(size_t number, size_t size);
unsigned long	get_time(unsigned long start_time);
void			*run_philo(void *arg);
void			print_what_philo_do(unsigned long time, int id, char *str,
					t_g_strukt *data);
int				is_int(char *num);
void			*ft_bzero(void *s, size_t len);
void			cool_exit(void);
void			ft_usleep(unsigned long start, int sleep_time,
					 t_g_strukt *data);

#endif