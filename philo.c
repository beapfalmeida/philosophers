#include "philosophers.h"

// uma a menos

static void	clear_everything(t_info *data)
{
	int	i;	

	i = -1;
	pthread_mutex_destroy(&(data->mutex));
	while (++i < data->n_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	free(data->philo);
}

static void	invalid_args()
{
	printf("Please provide the following arguments:\n");
	printf("<nb_of_philosophers> <time_to_die> <time_to_eat>");
	printf(" <time_to_sleep> [n. of times each must eat]\n");
}

static void	check_args(int ac, char **av, t_info *data)
{
	int	i;

	i = 1;
	while (av[i + 1])
	{
		if (!is_pos_num(av[i]))
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