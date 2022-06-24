/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/24 20:52:57 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat_and_more(t_philo *philo)
{
	if (!ft_check_die(philo) && !ft_check_eat(philo - (philo->id - 1)))
		ft_eat(philo);
	if (!ft_check_die(philo) && !ft_check_eat(philo - (philo->id - 1)))
		ft_sleep(philo, philo->data_ptr->tts * 1000);
	if (!ft_check_die(philo) && !ft_check_eat(philo - (philo->id - 1)))
		ft_think(philo);
	usleep(500);
}

void	*ft_loop(t_philo *philo)
{
	if (philo->data_ptr->nb_philo == 1)
	{
		ft_write(philo, LOCK_FORK);
		pthread_mutex_lock(&philo->data_ptr->check_die);
		philo->data_ptr->die = 1;
		pthread_mutex_unlock(&philo->data_ptr->check_die);
		usleep(philo->data_ptr->ttd * 1000);
		ft_write(philo, DIE);
		return (0);
	}
	if (philo->data_ptr->nb_philo % 2)
	{
		if (philo->id == philo->data_ptr->nb_philo)
			ft_usleep(philo, (philo->data_ptr->tte * 1000) * 2);
		else if (philo->id % 2)
			ft_usleep(philo, philo->data_ptr->tte * 1000);
	}
	else if (!(philo->data_ptr->nb_philo % 2) && (philo->id % 2))
		ft_usleep(philo, philo->data_ptr->tte * 1000);
	while (!ft_check_die(philo) && !ft_check_eat(philo - (philo->id - 1)))
		ft_eat_and_more(philo);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philo;

	if (!ft_fill_data_struct(argc, argv, &data))
		return (0);
	philo = ft_fill_philo_struct(&data);
	if (!philo)
		return (ft_destroy(&data), 0);
	data.philo_ptr = philo;
	if (ft_init_thread(&data, philo))
		return (0);
	return (ft_destroy(&data), free(philo), 0);
}
