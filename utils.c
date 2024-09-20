#include "philosophers.h"

//espaco para 1 funcao

void	wait_all_threads(t_info *data)
{
	while (!get_var(&(data->mutex), data->all_ready))
		;
}

void	print_info(t_philo *philo, long time, char c)
{
	pthread_mutex_lock(&(philo->data->write_mutex));
	if (c == 'e')
		printf("%ld %i is eating\n", time, philo->nb);
	else if (c == 's')
		printf("%ld %i is sleeping\n", time, philo->nb);
	else if (c == 't')
		printf("%ld %i is thinking\n", time, philo->nb);
	else if (c == 'f')
		printf("%ld %i has taken a fork\n", time, philo->nb);
	else if (c == 'd')
		printf("%ld %i died\n", time, philo->nb);
	pthread_mutex_unlock(&(philo->data->write_mutex));
}

int	is_pos_num(const char *str)
{
	int	i;

	i = 0;
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