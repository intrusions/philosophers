/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/09 05:17:12 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo, int time)
{
	printf("%ld - %d is sleeping\n", ft_get_time(), philo->id);
	usleep(time);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
	philo->last_eat = ft_get_time();
	printf("%ld   philo %d is eating\n", philo->last_eat, philo->id);
	usleep(philo->data_ptr->time_to_eat);
	pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
}

// t_bool	ft_check_eat(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	if (philo->data_ptr->number_of_philosophers != 1)
// 	{
// 		while (i < philo->data_ptr->number_of_philosophers)
// 		{
// 			if (philo[i].nb_meal < philo->data_ptr->number_of_times_each_philosophers_must_eat)
// 				return (0);
// 			i++;
// 		}
// 		return (1);
// 	}
// }

void	*ft_loop(t_philo *philo)
{
	if (philo->data_ptr->number_of_philosophers == 1)									// Si le philo est tout seul
	{
		printf("%ld - %d prend une fourchette\n", ft_get_time(), philo->id);
		usleep(philo->data_ptr->time_to_die);
		printf("%ld - %d est mort\n", ft_get_time(), philo->id);
		return (0);
	}
	if (philo->data_ptr->number_of_philosophers % 2)									// Si mon nombre de philo est impaire
	{
		if (philo->id == philo->data_ptr->number_of_philosophers)						// Si mon philo est le dernier des impaire
			ft_sleep(philo, philo->data_ptr->time_to_eat * 2);
		if (philo->id % 2)																// Si mon philo est inmpaire et que le nombre de philo est impaire
			ft_sleep(philo, philo->data_ptr->time_to_eat);
	}
	else if (philo->id % 2)																// Si mon philo est impaire dans un groupe de philo paire
		ft_sleep(philo, philo->data_ptr->time_to_eat);
	// while (!philo->die && !ft_check_eat(philo))
	// {
		
	// }
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (!ft_fill_data_struct(argc, argv, &data))
		return (0);
	philo = ft_fill_philo_struct(&data);
	data.philo_ptr = philo;
	if (!philo)
		return (0);
	if (ft_init_thread(&data, philo))
		return (0);
	free(philo);
}