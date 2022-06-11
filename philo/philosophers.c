/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/11 22:04:55 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat_and_more(t_philo *philo)
{
	if (!philo->data_ptr->die)
		ft_eat(philo);
	if (!philo->data_ptr->die)
		ft_sleep(philo, philo->data_ptr->time_to_sleep);
	if (!philo->data_ptr->die)
		ft_think(philo);
}

void	*ft_loop(t_philo *philo)
{
	if (philo->data_ptr->number_of_philosophers == 1)									// Si le philo est tout seul
	{
		ft_write(philo, LOCK_FORK);
		ft_write(philo, DIE);
		usleep(philo->data_ptr->time_to_die * 1000);
		philo->data_ptr->die = 1;
		return (0);
	}
	if (philo->data_ptr->number_of_philosophers % 2)									// Si le nombre de philo est impaire
	{
		if (philo->id == philo->data_ptr->number_of_philosophers)						// Si l'id du philo est le dernier des impaire
			usleep((philo->data_ptr->time_to_eat * 2) * 1000);
		if (philo->id % 2)																// Si l'id du philo est inmpaire et que le nombre de philo est impaire
			usleep(philo->data_ptr->time_to_eat * 1000);
	}
	else if (!(philo->data_ptr->number_of_philosophers % 2) && (philo->id % 2))			// Si l'id du philo est impaire dans un groupe de philo paire
		ft_sleep(philo, philo->data_ptr->time_to_eat);
	while (!philo->data_ptr->die && !ft_check_eat(philo - (philo->id - 1)))
		ft_eat_and_more(philo);															// Premier tour, les paire vont manger
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