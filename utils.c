/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:12:28 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/04 18:04:12 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_fill_struct(int argc, char **argv, t_data *data)
{
	ft_init_struct(data);
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosophers_must_eat = ft_atoi(argv[5]);
}

void	ft_init_struct(t_data *data)
{
	data->number_of_philosophers = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->number_of_times_each_philosophers_must_eat = 0;
}

int	ft_atoi(const char *str)
{
	size_t		i;
	long long	r;
	int			neg;

	i = 0;
	r = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (r * neg > 2147483647)
			return (-1);
		else if (r * neg < -2147483648)
			return (0);
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (neg * r);
}
