/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:58:32 by xel               #+#    #+#             */
/*   Updated: 2022/06/06 18:58:32 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	ft_fill_data_struct(int argc, char **argv, t_data *data)
{
	if (!ft_check_arg(argc, argv))
		return (0);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->number_of_philosophers <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (0);
	if (argc == 6)
	{
		data->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
		if (data->number_of_times_each_philosophers_must_eat <= 0)
			return (0);
	}
	else
		data->number_of_times_each_philosophers_must_eat = -1;
	if (pthread_mutex_init(&data->mutex, NULL))
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->fork)
		return (0);
	if (!ft_init_fork_and_check_die(data))
		return (0);
	return (1);
}

t_philo	*ft_fill_philo_struct(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * (data->number_of_philosophers));
	if (!philo)
		return (0);
	while (i < data->number_of_philosophers)
	{
		philo[i].data_ptr = data;
		philo[i].id = i + 1;
		philo[i].die = 0;
		philo[i].last_eat = 0;
		philo[i].nb_meal = 0;
		i++;
	}
	return (philo);
}

t_bool	ft_init_fork_and_check_die(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->check_die, NULL))
		return (0);
	return (1);
}

t_bool	ft_init_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, \
		(void *)&ft_loop, philo + i))
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
