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
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	t_philo			*philo;
}	t_info;

typedef struct s_philo
{
	t_info		*data;
	int			eat_count;
	int			nb;
	pthread_t	tid;
}	t_philo;

//utils
int		is_pos_num(const char *str);
int		ft_atoi(char *str);
void	print_info(t_philo *philo, char c);

//init
void	init_info(int ac, char **av, t_info *data);
void	init_philo(t_info *data, int i);
long	get_miliseconds();

//simulation
void	*simulate(void *arg);
void	grabfork(t_philo *philo);
void	dorpforks(t_philo *philo);
void	eat(t_philo *philo);

#endif