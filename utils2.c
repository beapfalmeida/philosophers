/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:14:12 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/10 12:15:02 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime_miliseconds(void)
{
	long			milisecs;
	struct timeval	time;

	gettimeofday(&time, NULL);
	milisecs = (1000 * time.tv_sec) + (time.tv_usec / 1000);
	return (milisecs);
}

long	get_chronometer(t_philo *philo)
{
	long	time;

	time = gettime_miliseconds() - philo->data->start_time;
	return (time);
}

int	get_var(pthread_mutex_t *mutex, int var)
{
	int	res;

	pthread_mutex_lock(mutex);
	res = var;
	pthread_mutex_unlock(mutex);
	return (res);
}

int	greater_zero(const char *str)
{
	int	i;

	i = 0;
	while (str[i + 1] && str[i] >= 48 && str[i] <= 57)
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	return (1);
}
