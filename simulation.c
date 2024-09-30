#include "philosophers.h"

int	check_if_died(t_philo *philo)
{
	if (get_chronometer(philo) - philo->last_meal >= philo->data->time_to_die)
	{
		set_var(&(philo->data->mutex), philo->dead, 1);
		print_info(philo, get_chronometer(philo), 'd');
		return (1);
	}
	return (0);
}

static void	think(t_philo *philo)
{
	if (!philo->dead)
		print_info(philo, get_chronometer(philo),'t');
	else
		exit(0);
}

static void	go_sleep(t_philo *philo)
{
	if (!philo->dead) // verificar se ninguem morreu;
	{
		print_info(philo, get_chronometer(philo),'s');
		usleep(philo->data->sleep_time);
	}
	else
		exit(0);
}

void	*simulate(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	wait_all_threads(philo->data);
	if (philo->data->max_eat == 0)
		return (NULL);
	while (1)	
	{
		grabfork(philo);
		eat(philo);
			//if (philo->eat_count == philo->data->max_eat) // como e que eu paro todas as threads?? seg fault quando todos comem 1 vez
			//break ;
		go_sleep(philo);
		think(philo);
		if (philo->dead)
			break ;
	}
	return (NULL);
}
