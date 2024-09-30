#include "philosophers.h"

void	grabfork(t_philo *philo)
{
	int left; // o meu
	int right; // o proximo

	if (!philo->dead)
	{
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
	else
	{
		print_info(philo, get_chronometer(philo), 'd');
		exit(0);
	}
}

void	dorpforks(t_philo *philo)
{
	int left; // o meu
	int right; // o proximo

	if (!philo->dead)
	{
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
	}
	else
		exit(0);
}

void	eat(t_philo *philo)
{
	if (!philo->dead)
	{
		print_info(philo, get_chronometer(philo), 'e');
		set_var(&(philo->data->mutex), philo->eat_count, philo->eat_count + 1);
		usleep(philo->data->eat_time);
		set_var(&(philo->data->mutex), philo->last_meal, get_chronometer(philo));
		dorpforks(philo);
		philo->last_meal = get_chronometer(philo);
	}
	else
		exit(0);
}
