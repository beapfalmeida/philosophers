#include "philosophers.h"

void	init_philo(t_info *data, int i)
{
	t_philo *philo;

	philo = &(data->philo[i]);
	philo->data = data;
	philo->nb = i + 1;
	philo->eat_count = 0;
	pthread_create(&(philo->tid), NULL, &simulate, philo);
}
void	init_mutexes(t_info *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&(data->write_mutex), NULL);
	while (++i < data->n_philo)
		pthread_mutex_init(&(data->forks[i]), NULL);
}

void	init_info(int ac, char **av, t_info *data)
{
	int	i;

	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]) * 1000;
	data->eat_time = ft_atoi(av[3]) * 1000;
	data->sleep_time = ft_atoi(av[4]) * 1000;
	if (ac == 6)
		data->max_eat = ft_atoi(av[5]);
	else
		data->max_eat = -1;
	data->start_time = get_miliseconds();
	data->philo = (t_philo *)malloc(data->n_philo * sizeof(t_philo));
	data->forks = (pthread_mutex_t *)malloc(data->n_philo * sizeof(pthread_mutex_t));
	init_mutexes(data);
	i = -1;
	while (++i < data->n_philo)
		init_philo(data, i);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].tid, NULL);
	i = -1;
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->write_mutex));
	free(data->philo);
}
