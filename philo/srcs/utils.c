/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:12:28 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/14 10:19:53 by xel              ###   ########.fr       */
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

t_bool	ft_check_max_eat(t_philo *philo)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	pthread_mutex_lock(&philo->data_ptr->check_max_eat);
	if (philo->data_ptr->max_eat == -1)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
		return (0);
	}
	else
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
	while (i < philo->data_ptr->nb_philo)
	{
		pthread_mutex_lock(&philo->data_ptr->check_max_eat);
		if (philo[i].nb_meal >= philo->data_ptr->max_eat)
			ret++;
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
		i++;
	}
	if (ret == (philo->data_ptr->nb_philo - 1))
		return (1);
	return (0);
}

t_bool	ft_check_die(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->check_die);
	if (!philo->data_ptr->die)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_die);
		return (0);
	}
	pthread_mutex_unlock(&philo->data_ptr->check_die);
	return (1);
}

void	ft_destroy(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	i = 0;
	free(data->fork);
	pthread_mutex_destroy(&data->mutex);
	pthread_mutex_destroy(&data->check_die);
	pthread_mutex_destroy(&data->check_time_eat);
	pthread_mutex_destroy(&data->check_max_eat);
}
