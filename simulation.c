#include "philosophers.h"

void	grabfork(t_philo *philo, char side)
{
	if (side == 'l')
	{
		// o primeiro vai buscar o garfo do último
		pthread_mutex_lock(philo->l_fork_mutex);
		if (philo->nb == 1)
		{
			if (!philo->data->philo[philo->data->n_philo - 1].my_fork)
			{
				philo->data->philo[philo->data->n_philo - 1].my_fork = 1;
				philo->l_fork = 1;
				print_info(philo, 'f');
			}
		}
		// os outros vao buscar o garfo do anterior
		else
		{
			// ex: se eu for o 2, vou buscar o garfo do 1, philo index 0
			if (!philo->data->philo[philo->nb - 2].my_fork)
			{
				philo->data->philo[philo->nb - 2].my_fork = 1;
				philo->l_fork = 1;
				print_info(philo, 'f');
			}
		}
	}
	else if (side == 'r')
	{
		pthread_mutex_lock(philo->r_fork_mutex);
		if (!philo->my_fork)
		{
			philo->my_fork = 1;
			philo->r_fork = 1;
		}
	}
}

void	eat(t_philo *philo)
{
	print_info(philo, 'e');
	usleep(philo->data->eat_time * 1000);
	// drop forks
	philo->l_fork = 0;
	if (philo->nb == 1)
		philo->data->philo[philo->data->n_philo - 1].my_fork = 0;
	else
		philo->data->philo[philo->nb - 2].my_fork = 0;
	philo->r_fork = 0;
	philo->my_fork = 0;
	pthread_mutex_unlock(philo->l_fork_mutex);
	pthread_mutex_unlock(philo->r_fork_mutex);
}

void	*simulate(void *arg)
{
	t_philo *philo = (t_philo*)arg;
	if (philo->nb % 2 == 0)
	{
		grabfork(philo, 'l');
		grabfork(philo, 'r');
	}
	else
	{
		usleep(100);
		grabfork(philo, 'r');
		grabfork(philo, 'l');
	}
	usleep(100);
	if (philo->l_fork && philo->r_fork)
		eat(philo);
	return (NULL);
}