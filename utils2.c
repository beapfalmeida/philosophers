#include "philosophers.h"

long	gettime_miliseconds()
{
	long	milisecs;
	struct timeval time;

	gettimeofday(&time, NULL);
	milisecs = (1000 * time.tv_sec) + (time.tv_usec / 1000);
	return (milisecs);
}

long	get_chronometer(t_philo *philo)
{
	long	time;

	time = gettime_miliseconds() - philo->data->start_time;
	return (time);
}

int	get_var(pthread_mutex_t *mutex, int var)
{
	int res;

	pthread_mutex_lock(mutex);
	res = var;
	pthread_mutex_unlock(mutex);
	return (res);
}

int	greater_zero(const char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] && str[i] >= 48 && str[i] <= 57)
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	return (1);
}