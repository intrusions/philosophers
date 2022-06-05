/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/05 03:23:15 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



void	*ft_routine(void *p_data, pthread_mutex_t *mutex)
{
	(void)p_data;
	pthread_mutex_lock(mutex);
	printf("coucou\n");
	pthread_mutex_unlock(mutex);
	return (NULL);
}

int	ft_init_thread(t_data *data, t_philo *philo, pthread_mutex_t *mutex)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, ft_routine, mutex))
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
	ft_fill_struct(argc, argv, &data);
	pthread_mutex_init(&mutex, NULL);
	philo = malloc(sizeof(t_philo) * (data.number_of_philosophers));
	if (!philo)
		return (0);
	if (!ft_init_thread(&data, philo, &mutex))
		return (0);
	pthread_join(philo[0].philo_thread, NULL);
	pthread_join(philo[1].philo_thread, NULL);
	pthread_join(philo[2].philo_thread, NULL);
	pthread_join(philo[3].philo_thread, NULL);
	pthread_join(philo[4].philo_thread, NULL);
	pthread_mutex_destroy(&mutex);
	// free(philo);
	// free(&philo[2]);
	// free(&philo[3]);
	// free(&philo[4]);
	// free(philo);
}

