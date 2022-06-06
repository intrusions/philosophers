/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/06 19:08:20 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_routine(void *mutex)
{
	pthread_mutex_lock(mutex);
	printf("coucou\n");
	pthread_mutex_unlock(mutex);
	return (NULL);
}

t_bool	ft_init_thread(t_data *data, t_philo *philo, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, &ft_routine, mutex))
			return (0);
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].philo_thread, NULL))
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo 		*philo;
	pthread_mutex_t	mutex;

	if (!(argc == 5 || argc == 6))
		return (0);
	if (!ft_fill_global_struct(argc, argv, &data))
		return (0);
	pthread_mutex_init(&mutex, NULL);
	philo = malloc(sizeof(t_philo) * (data.number_of_philosophers));
	if (!philo)
		return (0);
	if (!ft_init_thread(&data, philo, &mutex))
		return (0);
	pthread_mutex_destroy(&mutex);
	free(philo);
}

