/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:14:01 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/10 15:34:28 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	edge_cases(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		print_info(philo, 'f');
		return (1);
	}
	return (0);
}

static void	go_sleep(t_philo *philo)
{
	print_info(philo, 's');
	if (ft_usleep(philo, philo->data->sleep_time))
		return ;
	print_info(philo, 't');
}

void	*simulate(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&(philo->data->mutex));			
	pthread_mutex_unlock(&(philo->data->mutex));
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
	}
	return (NULL);
}
