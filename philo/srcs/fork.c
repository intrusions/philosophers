/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 03:38:23 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/11 22:14:32 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_lock(&philo->data_ptr->fork[philo->data_ptr->number_of_philosophers - 1]);
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
		ft_write(philo, LOCK_FORK);
		ft_write(philo, LOCK_FORK);
	}
	else
	{
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
		pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 2]);
		ft_write(philo, LOCK_FORK);
		ft_write(philo, LOCK_FORK);
	}
}

void	ft_unlock_fork(t_philo *philo)
{
	if (philo->id == 1)
	{
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->data_ptr->number_of_philosophers - 1]);
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
		pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 2]);
	}
}
