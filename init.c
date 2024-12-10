#include "philosophers.h"

//duas a menos

static void	init_philo(t_info *data, int i)
{
	t_philo *philo;

	philo = &(data->philo[i]);
	philo->data = data;
	philo->nb = i + 1;
	philo->eat_count = 0;
	philo->dead = 0;
	philo->last_meal = philo->data->start_time;
	philo->data->end = 0;
	philo->full = 0;
}

static void	init_mutexes(t_info *data)
{
	int	i;

	i = -1;
	pthread_mutex_init(&(data->mutex), NULL);
	while (++i < data->n_philo)
		pthread_mutex_init(&(data->forks[i]), NULL);
}

void	init_info(int ac, char **av, t_info *data)
{
	int	i;

	data->n_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->eat_time = ft_atol(av[3]);
	data->sleep_time = ft_atol(av[4]);
	if (ac == 6)
		data->max_eat = ft_atol(av[5]);
	if (ac != 6 || (av[5][0] == '0' && av[5][1] == '\0'))
		data->max_eat = -1;
	data->all_ready = 0;
	data->start_time = gettime_miliseconds();
	data->philo = (t_philo *)malloc(data->n_philo * sizeof(t_philo));
	data->forks = (pthread_mutex_t *)malloc(data->n_philo * sizeof(pthread_mutex_t));
	init_mutexes(data);
	i = -1;
	while (++i < data->n_philo)
		init_philo(data, i);
	i = -1;
	while (++i < data->n_philo)
		pthread_create(&(data->philo[i].tid), NULL, &simulate, &data->philo[i]);
	pthread_mutex_lock(&(data->mutex));
	data->all_ready = 1; // tirar (?)
	pthread_mutex_unlock(&(data->mutex));
	control(data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].tid, NULL);
}
