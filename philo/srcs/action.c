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

void	ft_write(t_philo *philo, int what_message)
{
	pthread_mutex_lock(&philo->data_ptr->mutex);
	if (what_message == THINK)
		printf(PINK "%ld - Philosophers %d is thinking\n", \
		ft_get_time() - philo->data_ptr->time, philo->id);
	else if (what_message == SLEEP)
		printf(YELLOW "%ld - Philosophers %d is sleeping\n", \
		ft_get_time() - philo->data_ptr->time, philo->id);
	else if (what_message == EAT)
		printf(BLUE "%ld - Philosophers %d is eating\n", \
		ft_get_time() - philo->data_ptr->time, philo->id);
	else if (what_message == LOCK_FORK)
		printf(CYAN "%ld - Philosophers %d has taken a fork\n", \
		ft_get_time() - philo->data_ptr->time, philo->id);
	else if (what_message == DIE)
		printf(RED "%ld - Philosophers %d hes died\n", \
		ft_get_time() - philo->data_ptr->time, philo->id);
	pthread_mutex_unlock(&philo->data_ptr->mutex);
}

void	ft_think(t_philo *philo)
{
	if (!ft_check_die(philo))
		ft_write(philo, THINK);
}

void	ft_sleep(t_philo *philo, int tts)
{
	if (!ft_check_die(philo))
	{
		ft_write(philo, SLEEP);
		usleep(tts * 1000);
	}
}

void	ft_eat(t_philo *philo)
{
	if (!ft_check_die(philo))
	{
		ft_lock_fork(philo);
		pthread_mutex_lock(&philo->data_ptr->check_last_eat);
		philo->last_eat = ft_get_time() - philo->data_ptr->time;
		pthread_mutex_unlock(&philo->data_ptr->check_last_eat);
		pthread_mutex_lock(&philo->data_ptr->check_max_eat);
		philo->nb_meal++;
		pthread_mutex_unlock(&philo->data_ptr->check_max_eat);
		ft_write(philo, EAT);
		usleep(philo->data_ptr->tte * 1000);
		ft_unlock_fork(philo);
	}
}

void	ft_death(t_data *data, t_philo *philo)
{
	int	i;

	while (!ft_check_die(philo))
	{
		i = 0;
		while (i < data->nb_philo)
		{
			pthread_mutex_lock(&philo->data_ptr->check_last_eat);
			if ((ft_get_time() - data->time - philo[i].last_eat) >= data->ttd)
			{
				pthread_mutex_unlock(&philo->data_ptr->check_last_eat);
				pthread_mutex_lock(&philo->data_ptr->check_die);
				data->die = philo->id;
				pthread_mutex_unlock(&philo->data_ptr->check_die);
				ft_write(philo + i, DIE);
				return ;
			}
			else
				pthread_mutex_unlock(&philo->data_ptr->check_last_eat);
			i++;
		}	
	}
}
