/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/09 18:53:34 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_loop(t_philo *philo)
{
	if (philo->data_ptr->number_of_philosophers == 1)									// Si le philo est tout seul
	{
		printf("%ld - %d prend une fourchette\n", ft_get_time(), philo->id);
		usleep(philo->data_ptr->time_to_die);
		printf("%ld - %d est mort\n", ft_get_time(), philo->id);
		return (0);
	}
	if (philo->data_ptr->number_of_philosophers % 2)									// Si le nombre de philo est impaire
	{
		if (philo->id == philo->data_ptr->number_of_philosophers)						// Si l'id du philo est le dernier des impaire
			ft_sleep(philo, philo->data_ptr->time_to_eat * 2);
		if (philo->id % 2)																// Si l'id du philo est inmpaire et que le nombre de philo est impaire
			ft_sleep(philo, philo->data_ptr->time_to_eat);
	}
	else if (!(philo->data_ptr->number_of_philosophers % 2) && (philo->id % 2))			// Si l'id du philo est impaire dans un groupe de philo paire
		ft_sleep(philo, philo->data_ptr->time_to_eat);
	while (!philo->die && !ft_check_eat(philo - (philo->id - 1)))
	{
		printf("coucou\n");
	}
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