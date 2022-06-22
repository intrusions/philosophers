/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 18:02:08 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/22 18:20:02 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
