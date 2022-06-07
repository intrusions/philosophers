/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/08 00:59:00 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_philo *philo)
{
	printf("%ld   philo %d is sleeping\n", ft_print_time(), philo->id);
	usleep(philo->data_ptr->time_to_sleep);
	printf("%ld   philo %d is stop sleeping\n", ft_print_time(), philo->id);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data_ptr->fork[philo->id - 1]);
	philo->last_eat = ft_print_time();
	printf("%ld   philo %d is eating\n", philo->last_eat, philo->id);
	usleep(philo->data_ptr->time_to_eat);
	pthread_mutex_unlock(&philo->data_ptr->fork[philo->id - 1]);
	printf("%ld   philo %d is stop eating\n", ft_print_time(), philo->id);
}

void	*ft_loop(t_philo *philo)
{
	if (!(philo->id % 2))
		ft_eat(philo);
	else if (philo->id % 2)
		ft_sleep(philo);
	return (NULL);
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
