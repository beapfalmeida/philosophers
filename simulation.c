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
		print_info(philo, 'f');
		pthread_mutex_lock(&(philo->data->forks[right]));
		print_info(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[right]));
		print_info(philo, 'f');
		pthread_mutex_lock(&(philo->data->forks[left]));
		print_info(philo, 'f');
	}
}

void	dorpforks(t_philo *philo)
{
	int left; // o meu
	int right; // o proximo

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

void	eat(t_philo *philo)
{
	// verificar se nao está morto
	print_info(philo, 'e');

	philo->eat_count++;

	usleep(philo->data->eat_time);
	dorpforks(philo);
}

void	think(t_philo *philo)
{
	//verificar se nao está morto
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
	//wait_all_threads_ready(); TODO
	if (philo->data->max_eat == 0)
		return (NULL);
	while (1)	
	{
		grabfork(philo);
		eat(philo);
			if (philo->eat_count == philo->data->max_eat) // como e que eu paro todas as threads?? seg fault quando todos comem 1 vez
			break ;
		go_sleep(philo);
		think(philo);
	}
	return (NULL);
}
