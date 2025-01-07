/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpaiva-f <bpaiva-f@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:13:56 by bpaiva-f          #+#    #+#             */
/*   Updated: 2025/01/07 16:09:24 by bpaiva-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	clear_everything(t_info *data)
{
	int	i;	

	i = -1;
	pthread_mutex_destroy(&(data->mutex));
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	free(data->philo);
	free(data->forks);
}

static void	invalid_args(void)
{
	write(2, "Please provide the following arguments:\n", 40);
	write(2, "<nb_of_philosophers> <time_to_die> <time_to_eat>", 48);
	write(2, " <time_to_sleep> [n. of times each must eat]\n", 46);
}

static void	check_args(int ac, char **av, t_info *data)
{
	int	i;

	i = 1;
	while (av[i + 1])
	{
		if (ft_atol(av[i]) > 2147483647
			|| ft_atol(av[i]) < 0 || !is_pos_num(av[i]))
		{
			invalid_args();
			return ;
		}
		i++;
	}
	if (!greater_zero(av[i]))
	{
		invalid_args();
		return ;
	}
	init_info(ac, av, data);
	clear_everything(data);
}

int	main(int ac, char **av)
{
	t_info	data;

	if (ac == 5 || ac == 6)
		check_args(ac, av, &data);
	else
		invalid_args();
	return (0);
}
