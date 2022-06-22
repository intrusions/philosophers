/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:12:28 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/23 00:00:04 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	pthread_mutex_lock(&philo->data_ptr->check_max_eat);
	if (philo->data_ptr->max_eat == -1)
	{
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
		return (0);
	}
	while (i < philo->data_ptr->nb_philo)
	{
		if (philo[i].nb_meal < philo->data_ptr->max_eat)
		{
			pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
			return (0);
		}
		i++;
	}
	pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
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
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->check_die);
	pthread_mutex_destroy(&data->check_max_eat);
	pthread_mutex_destroy(&data->check_last_eat);
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

void	ft_usleep(t_philo *philo, int tts)
{
	if (!ft_check_die(philo))
		usleep(tts);
}
