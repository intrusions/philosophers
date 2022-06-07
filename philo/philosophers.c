/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/07 04:27:14 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->fork[philo->id -1]);
	printf("philo->id = %d\n", philo->id);
	pthread_mutex_unlock(&philo->data_ptr->fork[philo->id -1]);
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_data			data;
	t_philo 		*philo;

	if (!ft_fill_data_struct(argc, argv, &data))
		return (0);
	philo = ft_fill_philo_struct(&data);
	data.philo_ptr = philo;
	if (!philo)
		return (0);
	if (!ft_init_thread(&data, philo))
		return (0);
	free(philo);
}