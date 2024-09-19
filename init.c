#include "philosophers.h"

void	init_philo(t_info *data, int i)
{
	t_philo philo;

	philo = data->philo[i];
	philo.data = data;
	philo.nb = i + 1;
	pthread_create(&(philo.tid), NULL, &simulate, &philo);
}

void	init_info(int ac, char **av, t_info *data)
{
	int	i;

	i = -1;
	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->eat_time = ft_atoi(av[3]);
	data->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = 0;
	data->start_time = get_miliseconds();
	data->philo = (t_philo *)malloc(data->n_philo * sizeof(t_philo));
	data->forks = (pthread_mutex_t *)malloc(data->n_philo * sizeof(pthread_mutex_t));
	//pthread_mutex_init(&(data->write_mutex), NULL);
	while (++i < data->n_philo)
		pthread_mutex_init(&(data->forks[i]), NULL);
	i = 0;
	while (i < data->n_philo)
	{
		init_philo(data, i);
		i++;
	}
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].tid, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	//pthread_mutex_destroy(&(data->write_mutex));
	free(data->philo);
}
