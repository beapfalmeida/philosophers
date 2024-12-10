/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:14:01 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/10 12:18:31 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	edge_cases(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex));
	if (philo->data->max_eat == 0)
	{
		pthread_mutex_unlock(&(philo->data->mutex));
		return (1);
	}
	if (philo->data->n_philo == 1)
	{
		pthread_mutex_unlock(&(philo->data->mutex));
		pthread_mutex_lock(&(philo->data->forks[0]));
		pthread_mutex_unlock(&(philo->data->forks[0]));
		print_info(philo, get_chronometer(philo), 'f');
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->mutex));
	return (0);
}

static void	think(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&(philo->data->mutex));
	time = get_chronometer(philo);
	pthread_mutex_unlock(&(philo->data->mutex));
	print_info(philo, time, 't');
}

static void	go_sleep(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&(philo->data->mutex));
	time = get_chronometer(philo);
	pthread_mutex_unlock(&(philo->data->mutex));
	print_info(philo, time, 's');
	ft_usleep(philo, philo->data->sleep_time);
}

void	*simulate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (edge_cases(philo))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&(philo->data->mutex));
		if (philo->data->end == 1)
		{
			pthread_mutex_unlock(&(philo->data->mutex));
			return (NULL);
		}
		pthread_mutex_unlock(&(philo->data->mutex));
		grabfork(philo);
		eat(philo);
		go_sleep(philo);
		think(philo);
	}
	return (NULL);
}
