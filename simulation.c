#include "philosophers.h"

void	died(t_philo *philo)
{
	if (get_chronometer(philo) >= philo->data->time_to_die && !philo->full)
	{
		set_var(&(philo->data->mutex), philo->dead, 1);
		print_info(philo, get_chronometer(philo), 'd');
	}
}

static void	think(t_philo *philo)
{
	if (!philo->dead)
		print_info(philo, get_chronometer(philo),'t');
}

static void	go_sleep(t_philo *philo)
{
	if (!philo->dead)
	{
		print_info(philo, get_chronometer(philo),'s');
		usleep(philo->data->sleep_time);
	}
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
	}
	return (NULL);
}
