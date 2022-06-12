/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:12:28 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/12 02:20:02 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	size_t		i;
	long long	r;
	int			neg;

	i = 0;
	r = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (r * neg > INT_MAX)
			return (0);
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (neg * r);
}

long	ft_get_time(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

t_bool	ft_check_eat(t_philo *philo)
{
	int	i;

	i = 0;
	if (philo->data_ptr->number_of_times_each_philosophers_must_eat == -1)
		return (0);
	while (i < philo->data_ptr->number_of_philosophers)
	{
		if (philo[i].nb_meal < philo->data_ptr->number_of_times_each_philosophers_must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	i = 0;
	free(data->fork);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->check_die);
}