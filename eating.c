#include "philosophers.h"

void	grabfork(t_philo *philo)
{
	int left; // o meu
	int right; // o proximo

	left = philo->nb - 1;
	right = philo->nb;
	if (philo->nb == philo->data->n_philo)
		right = 0;
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[left]));
		print_info(philo, get_chronometer(philo), 'f');
		pthread_mutex_lock(&(philo->data->forks[right]));
		print_info(philo, get_chronometer(philo), 'f');
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[right]));
		print_info(philo, get_chronometer(philo), 'f');
		pthread_mutex_lock(&(philo->data->forks[left]));
		print_info(philo, get_chronometer(philo), 'f');
	}
}

void	dorpforks(t_philo *philo)
{
	int left; // o meu
	int right; // o proximo

	//pthread_mutex_lock(&(philo->data->mutex));
	left = philo->nb - 1;
	right = philo->nb;
	if (philo->nb == philo->data->n_philo)
		right = 0;
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->data->forks[right]));
		pthread_mutex_unlock(&(philo->data->forks[left]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks[left]));
		pthread_mutex_unlock(&(philo->data->forks[right]));
	}
	//pthread_mutex_unlock(&(philo->data->mutex));
}

void	eat(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&(philo->data->mutex));
	time = get_chronometer(philo);
	pthread_mutex_unlock(&(philo->data->mutex));
	print_info(philo, time, 'e');
	pthread_mutex_lock(&(philo->data->mutex));
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->data->mutex));
	pthread_mutex_lock(&(philo->data->mutex));
	philo->last_meal = gettime_miliseconds();
	pthread_mutex_unlock(&(philo->data->mutex));
	ft_usleep(philo, philo->data->eat_time);
	dorpforks(philo);
}
