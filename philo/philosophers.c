/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/07 03:27:42 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->mutex);
	printf("philo->id = %d\n", philo->id);
	pthread_mutex_unlock(&philo->data_ptr->mutex);
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_data			data;
	t_philo 		*philo;

	if (!ft_fill_global_struct(argc, argv, &data))
		return (0);
	philo = ft_fill_philo(&data);
	if (!philo)
		return (0);
	if (!ft_init_thread(&data, philo))
		return (0);
	free(philo);
}