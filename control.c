#include "philosophers.h"

//se der erro na thread tenho de ter isso em conta
void control(t_info *data)
{
	int	i;
	i = 0;

	pthread_mutex_lock(&(data->mutex));
	pthread_mutex_unlock(&(data->mutex));
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

int	check_if_died(pthread_mutex_t *mutex, t_philo *philo)
{
	long	time;

	pthread_mutex_lock(mutex);
	if (gettime_miliseconds() - philo->last_meal >= philo->data->time_to_die)
	{
		philo->dead = 1;
		philo->data->end = 1;
		time = get_chronometer(philo);
		pthread_mutex_unlock(mutex);
		print_info(philo, time, 'd');
		return (1);
	}
	pthread_mutex_unlock(mutex);
	return (0);
}
