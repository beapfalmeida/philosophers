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
	int	i;

	i = 0;
	pthread_mutex_lock(&(philo->data->mutex));
	while (i < philo->data->n_philo)
	{
		if (!philo[i].full)
		{
			pthread_mutex_unlock(&(philo->data->mutex));
			return (0);
		}
		i++;
	}
	philo->data->end = 1;
	pthread_mutex_unlock(&(philo->data->mutex));
	return (1);
}

void	control(t_info *data)
{
	int	i;

	pthread_mutex_lock(&(data->mutex));
	pthread_mutex_unlock(&(data->mutex));
	i = 0;
	while (1)
	{
		if (check_all_ate(data->philo))
			return ;
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_lock(&(data->mutex));
			if (data->philo[i].eat_count == data->max_eat)
				data->philo[i].full = 1;
			pthread_mutex_unlock(&(data->mutex));
			if (check_if_died(&(data->mutex), &(data->philo[i])))
				return ;
			i++;
		}
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
	if (starved(mutex, philo))
	{
		pthread_mutex_lock(mutex);
		philo->data->end = 1;
		pthread_mutex_unlock(mutex);
		print_info(philo, 'd');
		return (1);
	}
	return (0);
}
