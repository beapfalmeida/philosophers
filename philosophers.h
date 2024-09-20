#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
#include <sys/time.h>


typedef struct s_philo t_philo;

typedef struct s_info
{
	int				n_philo;
	int				time_to_die;
	int				eat_time;
	int				sleep_time;
	int				max_eat;
	long			start_time;
	int				all_ready;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	mutex;
	t_philo			*philo;
	pthread_t		control_tid;
}	t_info;

typedef struct s_philo
{
	t_info		*data;
	int			dead;
	int			full;
	int			eat_count;
	int			nb;
	pthread_t	tid;
}	t_philo;

//utils - full 
int		is_pos_num(const char *str);
int		ft_atoi(char *str);
void	print_info(t_philo *philo, long time, char c);
void	wait_all_threads(t_info *data);

//eat
void	grabfork(t_philo *philo);
void	dorpforks(t_philo *philo);
void	eat(t_philo *philo);

long	gettime_miliseconds();
int		get_var(pthread_mutex_t *mutex, int var);
long	get_chronometer(t_philo *philo);
void	set_var(pthread_mutex_t *mutex, int var, int set);

void	init_info(int ac, char **av, t_info *data);

void	*simulate(void *arg);
void	*control(void *arg);

#endif