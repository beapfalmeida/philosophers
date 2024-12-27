/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:03 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/27 16:37:34 by bpaiva-f         ###   ########.fr       */
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
		printf("Each philo ate his respective meals!\n");
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->mutex));
	return (0);
}

void	control(t_info *data)
{
	while (1)
	{
		if (check_if_died(data->philo)
			|| check_all_ate(data->philo))
			return ;
	}
}

int	starved(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex));
	if (gettime_miliseconds() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->data->mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->data->mutex));
	return (0);
}

int	check_if_died(t_philo *philo)
{
	int	i;
	int	n;

	i = 0;
	pthread_mutex_lock(&(philo->data->mutex));
	n = philo->data->n_philo;
	pthread_mutex_unlock(&(philo->data->mutex));
	while (i < n)
	{
		if (starved(&philo[i]))
		{
			pthread_mutex_lock(&(philo->data->mutex));
			philo->data->end = 1;
			pthread_mutex_unlock(&(philo->data->mutex));
			print_info(&philo[i], 'd');
			return (1);
		}
		i++;
	}
	return (0);
}
