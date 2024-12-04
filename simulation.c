#include "philosophers.h"

static void	think(t_philo *philo)
{
	long	time;
	
	pthread_mutex_lock(&(philo->data->mutex));
	time = get_chronometer(philo);
	pthread_mutex_unlock(&(philo->data->mutex));
	print_info(philo, time,'t');
}

static void	go_sleep(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&(philo->data->mutex));
	time = get_chronometer(philo);
	pthread_mutex_unlock(&(philo->data->mutex));
	print_info(philo, time,'s');
	usleep(philo->data->sleep_time);
}

void	*simulate(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if (philo->data->max_eat == 0)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mutex));
		if (philo->data->end == 1)
		{
			pthread_mutex_unlock(&(philo->data->mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->mutex));
		grabfork(philo);
		eat(philo);
		go_sleep(philo);
		think(philo);
	}
	return (NULL);
}
