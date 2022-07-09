/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 00:32:53 by jucheval          #+#    #+#             */
/*   Updated: 2022/07/09 23:26:35 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_bool	ft_check_input_value(int argc, char **argv, t_data *data)
{
	if ((data->nb_philo <= 0)
		|| data->ttd <= 0 || data->tte <= 0 || data->tts <= 0)
		return (0);
	if (argc == 6)
	{
		data->max_eat = ft_atoi(argv[5]);
		if (data->max_eat <= 0)
			return (0);
	}
	else
		data->max_eat = -1;
	return (1);
}

t_bool	ft_check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (!(argc == 5 || argc == 6))
		return (0);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
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
		if (r * neg > INT_MAX)
			return (0);
		r = r * 10 + (str[i] - 48);
		i++;
	}
	return (neg * r);
}
