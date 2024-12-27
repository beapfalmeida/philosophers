/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:14:03 by bpaiva-f          #+#    #+#             */
/*   Updated: 2024/12/27 14:20:38 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_usleep(t_philo *philo, long wait_time)
{
	long	st;

	st = gettime_miliseconds();
	while (gettime_miliseconds() - st < wait_time)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->end)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->mutex);
	}
	return (0);
}

void	print_info(t_philo *philo, char c)
{
	long	time;

	pthread_mutex_lock(&(philo->data->mutex));
	time = get_chronometer(philo);
	if (c == 'd')
		printf("%ld %i died\n", time, philo->nb);
	if (philo->data->end)
	{
		pthread_mutex_unlock(&(philo->data->mutex));
		return ;
	}
	if (c == 'e')
		printf("%ld %i is eating\n", time, philo->nb);
	else if (c == 's')
		printf("%ld %i is sleeping\n", time, philo->nb);
	else if (c == 't')
		printf("%ld %i is thinking\n", time, philo->nb);
	else if (c == 'f')
		printf("%ld %i has taken a fork\n", time, philo->nb);
	else if (c == 'p')
		printf("%ld %i droped a fork\n", time, philo->nb);
	pthread_mutex_unlock(&(philo->data->mutex));
}

int	is_pos_num(const char *str)
{
	int	i;

	i = 0;
	if (str[i + 1] == '\0' && str[i] == '0')
		return (0);
	while (str[i + 1] && str[i] >= 48 && str[i] <= 57)
		i++;
	if (str[i] < '0' || str[i] > '9')
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result = result + str[i] - 48;
		i++;
	}
	return (result);
}

long	ft_atol(const char *str)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
		{
			sign *= -1;
		}
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result * sign);
}
