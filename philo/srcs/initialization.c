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
	data->nb_philo = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	data->time = ft_get_time();
	data->die = 0;
	if (!ft_check_input_value(argc, argv, data))
		return (0);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (0);
	if (!ft_init_fork_and_mutex(data))
		return (ft_destroy(data), 0);
	return (1);
}

t_philo	*ft_fill_philo_struct(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!philo)
		return (0);
	while (i < data->nb_philo)
	{
		philo[i].data_ptr = data;
		philo[i].id = i + 1;
		philo[i].last_eat = 0;
		philo[i].nb_meal = 0;
		i++;
	}
	return (philo);
}

t_bool	ft_init_fork_and_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL))
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->write, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_max_eat, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_last_eat, NULL))
		return (0);
	if (pthread_mutex_init(&data->check_die, NULL))
		return (0);
	return (1);
}

t_bool	ft_init_thread(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo[i].philo_thread, NULL, \
		(void *)&ft_loop, philo + i))
			return (0);
		i++;
	}
	i = 0;
	usleep(50);
	ft_death(data, philo);
	while (i < data->nb_philo)
	{
		if (pthread_join(philo[i].philo_thread, NULL))
			return (0);
		i++;
	}
	ft_destroy(data);
	free(philo);
	return (1);
}
