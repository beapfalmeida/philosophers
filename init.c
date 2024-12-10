/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:16 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/10 15:31:30 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philo(t_info *data, int i)
{
	t_philo	*philo;

	philo = &(data->philo[i]);
	philo->data = data;
	philo->nb = i + 1;
	philo->eat_count = 0;
	philo->last_meal = philo->data->start_time;
	philo->data->end = 0;
	philo->full = 0;
	philo->left = i;
	philo->right = (i + 1) % philo->data->n_philo;
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
	data->start_time = gettime_miliseconds();
	data->philo = (t_philo *)malloc(data->n_philo * sizeof(t_philo));
	data->forks = malloc(data->n_philo * sizeof(pthread_mutex_t));
	init_mutexes(data);
	i = -1;
	while (++i < data->n_philo)
		init_philo(data, i);
	i = -1;
	while (++i < data->n_philo)
		pthread_create(&(data->philo[i].tid), NULL, &simulate, &data->philo[i]);
	control(data);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->philo[i].tid, NULL);
}
