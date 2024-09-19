#include "philosophers.h"

void	grabfork(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->nb % philo->data->n_philo]));
		print_info(philo, 'f');
		pthread_mutex_lock(&(philo->data->forks[philo->nb - 1]));
		print_info(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->nb - 1]));
		print_info(philo, 'f');
		pthread_mutex_lock(&(philo->data->forks[philo->nb % philo->data->n_philo]));
		print_info(philo, 'f');
	}
}

void	dorpforks(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->nb % philo->data->n_philo]));
		pthread_mutex_unlock(&(philo->data->forks[philo->nb - 1]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->nb - 1]));
		pthread_mutex_unlock(&(philo->data->forks[philo->nb % philo->data->n_philo]));
	}
	printf("forks droped\n");
}

void	eat(t_philo *philo)
{
	// verificar se nao está morto
	print_info(philo, 'e');
	usleep(philo->data->eat_time);
}

void	think(t_philo *philo)
{
	// verificar se nao está morto
	print_info(philo, 't');
}

void	go_sleep(t_philo *philo)
{
	// verificar se nao está morto
	print_info(philo, 's');
	usleep(philo->data->sleep_time);
}

void	*simulate(void *arg)
{
	t_philo *philo = (t_philo*)arg;

	while (1)
	{
		grabfork(philo);
		eat(philo);
		dorpforks(philo);
		go_sleep(philo);
		think(philo);
	}
	return (NULL);
}