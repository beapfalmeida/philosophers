#include "philosophers.h"

void	grabfork(t_philo *philo, char side)
{
	//pthread_mutex_lock(philo->data->mutex);
	print_info(philo, 'f');
	if (side == 'l')
		philo->l_fork = 1;
	else if (side == 'r')
		philo->r_fork = 1;
}

void	eat(t_philo *philo)
{
	print_info(philo, 'e');
	usleep(philo->data->eat_time * 1000);
	pthread_mutex_unlock(philo->data->mutex);
}

void	*simulate(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	if (philo->nb % 2 == 0)
		grabfork(philo, 'l');
	else
		printf("im the other one, %d\n", philo->nb);
	if (philo->nb % 2 == 0)
		grabfork(philo, 'r');
	else
		printf("im the other one, %d\n", philo->nb);
	if (philo->l_fork && philo->r_fork)
		eat(philo);
	return (NULL);
}