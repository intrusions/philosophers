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

t_bool	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' && argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_bool	ft_fill_global_struct(int argc, char **argv, t_data *data)
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
	return (1);
}