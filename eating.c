/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:07 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/10 16:23:03 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	grabfork(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->left]));
		pthread_mutex_lock(&(philo->data->forks[philo->right]));
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->right]));
		pthread_mutex_lock(&(philo->data->forks[philo->left]));
	}
	print_info(philo, 'f');
	print_info(philo, 'f');
}

void	dropforks(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->right]));
		pthread_mutex_unlock(&(philo->data->forks[philo->left]));
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->left]));
		pthread_mutex_unlock(&(philo->data->forks[philo->right]));
	}
}

void	eat(t_philo *philo)
{
	print_info(philo, 'e');
	pthread_mutex_lock(&(philo->data->mutex));
	philo->eat_count++;
	philo->last_meal = gettime_miliseconds();
	if (philo->eat_count == philo->data->max_eat)
		philo->data->all_ate++;
	pthread_mutex_unlock(&(philo->data->mutex));
	ft_usleep(philo, philo->data->eat_time);
	dropforks(philo);
}
