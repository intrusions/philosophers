/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 18:53:09 by xel               #+#    #+#             */
/*   Updated: 2022/06/09 18:53:09 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo, int time_to_sleep)
{
	printf("%ld - %d is sleeping\n", ft_get_time(), philo->id);
	usleep(time_to_sleep);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
	philo->last_eat = ft_get_time();
	printf("%ld   philo %d is eating\n", philo->last_eat, philo->id);
	usleep(philo->data_ptr->time_to_eat);
	pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
}
