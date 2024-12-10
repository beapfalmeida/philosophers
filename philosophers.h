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
	long			time_to_die;
	long				eat_time;
	long				sleep_time;
	int				max_eat;
	long			start_time;
	int				all_ready;
	int				end;
	pthread_mutex_t	*forks;
	pthread_mutex_t mutex;
	t_philo			*philo;
}	t_info;

typedef struct s_philo
{
	t_info		*data;
	int			dead;
	long		last_meal;
	int			eat_count;
	int			nb;
	int			full;
	pthread_t	tid;
}	t_philo;

//utils
int		is_pos_num(const char *str);
int		ft_atoi(char *str);
long	ft_atol(const char *str);
void	print_info(t_philo *philo, long time, char c);

// utils2
long	gettime_miliseconds();
int		get_var(pthread_mutex_t *mutex, int var);
long	get_chronometer(t_philo *philo);
void	ft_usleep(t_philo *philo, long wait_time);
int		greater_zero(const char *str);

//eat
void	grabfork(t_philo *philo);
void	dorpforks(t_philo *philo);
void	eat(t_philo *philo);

// init
void	init_info(int ac, char **av, t_info *data);

void	*simulate(void *arg);
int		check_if_died(pthread_mutex_t *mutex, t_philo *philo);
void 	control(t_info *data);

#endif