/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:03 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/10 16:25:49 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_all_ate(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex));
	if (philo->data->all_ate == philo->data->n_philo)
	{
		philo->data->end = 1;
		pthread_mutex_unlock(&(philo->data->mutex));
		printf("Each philo ate his respective meal!\n");
		return (0);
	}
	pthread_mutex_unlock(&(philo->data->mutex));
	return (1);
}

void	control(t_info *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;

			if (check_if_died(&(data->mutex), data->philo)
				|| check_all_ate(data->philo))
				return ;
			i++;
		}
	}

int	starved(pthread_mutex_t *mutex, t_philo *philo)
{
	pthread_mutex_lock(mutex);
	if (gettime_miliseconds() - philo->last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->data->mutex));
		return (1);
	}
	pthread_mutex_unlock(mutex);
	return (0);
}

int	check_if_died(pthread_mutex_t *mutex, t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->n_philo)
	{
		if (starved(mutex, &philo[i]))
		{
			pthread_mutex_lock(mutex);
			philo->data->end = 1;
			pthread_mutex_unlock(mutex);
			print_info(philo, 'd');
			return (1);
		}
	}
	return (0);
}
