#include "philosophers.h"

void control(t_info *data)
{
	int	i;
	i = 0;

	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (check_if_died(&(data->mutex), &(data->philo[i])))
				return ;
			i++;
		}
	}
}

static int	starved(pthread_mutex_t *mutex, t_philo *philo)
{
	pthread_mutex_lock(mutex);
	if (gettime_miliseconds() - philo->last_meal >= philo->data->time_to_die)
	{

		pthread_mutex_unlock(&(philo->data->mutex));
		return (1);
	}
	pthread_mutex_unlock(mutex);
	return (0);
}
int	check_if_died(pthread_mutex_t *mutex, t_philo *philo)
{
	long	time;

	if (starved(mutex, philo))
	{
		pthread_mutex_lock(mutex);
		philo->dead = 1;
		philo->data->end = 1;
		time = get_chronometer(philo);
		pthread_mutex_unlock(mutex);
		print_info(philo, time, 'd');
		return (1);
	}
	return (0);
}
