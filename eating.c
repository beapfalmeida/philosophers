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
		print_info(philo, 'f');
		pthread_mutex_lock(&(philo->data->forks[philo->right]));
		print_info(philo, 'f');
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->right]));
		print_info(philo, 'f');
		pthread_mutex_lock(&(philo->data->forks[philo->left]));
		print_info(philo, 'f');
	}
}

void	dropforks(t_philo *philo)
{
	if (philo->nb % 2 == 0)
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->right]));
		print_info(philo, 'p');
		pthread_mutex_unlock(&(philo->data->forks[philo->left]));
		print_info(philo, 'p');
	}
	else
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->left]));
		print_info(philo, 'p');
		pthread_mutex_unlock(&(philo->data->forks[philo->right]));
		print_info(philo, 'p');
	}
}

void	eat(t_philo *philo)
{
	print_info(philo, 'e');
	philo->eat_count++;
	philo->last_meal = gettime_miliseconds();
	pthread_mutex_lock(&(philo->data->mutex));
	if (philo->eat_count == philo->data->max_eat)
		philo->data->all_ate++;
	pthread_mutex_unlock(&(philo->data->mutex));
	usleep(philo->data->eat_time * 1000);
	dropforks(philo);
}
