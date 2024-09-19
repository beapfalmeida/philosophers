#include "philosophers.h"

void	print_info(t_philo *philo, char c)
{
	long	time;

	pthread_mutex_lock(&(philo->data->write_mutex));
	time = get_miliseconds() - philo->data->start_time;
	if (c == 'e')
	{
		printf("%ld %i is eating\n", time, philo->nb);
		philo->eat_count++;
	}
	else if (c == 's')
		printf("%ld %i is sleeping\n", time, philo->nb);
	else if (c == 't')
		printf("%ld %i is thinking\n", time, philo->nb);
	else if (c == 'f')
		printf("%ld %i has taken a fork\n", time, philo->nb);
	pthread_mutex_unlock(&(philo->data->write_mutex));
}
long	get_miliseconds()
{
	long	milisecs;
	struct timeval time;
	gettimeofday(&time, NULL);
	milisecs = (1000 * time.tv_sec) + (time.tv_usec / 1000);
	return (milisecs);
}

int	is_pos_num(const char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] && str[i] >= 48 && str[i] <= 57)
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result = result + str[i] - 48;
		i++;
	}
	return (result);
}