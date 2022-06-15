/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:06:55 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/15 10:22:36 by xel              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat_and_more(t_philo *philo)
{
	if (!ft_check_die(philo))
		ft_eat(philo);
	if (!ft_check_die(philo))
		ft_sleep(philo, philo->data_ptr->tts);
	if (!ft_check_die(philo))
		ft_think(philo);
}

void	*ft_loop(t_philo *philo)
{
	if (philo->data_ptr->nb_philo == 1)
	{
		ft_write(philo, LOCK_FORK);
		pthread_mutex_lock(&philo->data_ptr->check_die);
		philo->data_ptr->die = 1;
		pthread_mutex_unlock(&philo->data_ptr->check_die);
		ft_write(philo, DIE);
		usleep(philo->data_ptr->ttd * 1000);
		return (0);
	}
	if (philo->data_ptr->nb_philo % 2)
	{
		if (philo->id == philo->data_ptr->nb_philo)
			usleep((philo->data_ptr->tte * 2) * 900);
		else if (philo->id % 2)
			usleep(philo->data_ptr->tte * 1000);
	}
	else if (!(philo->data_ptr->nb_philo % 2) && (philo->id % 2))
		usleep(philo->data_ptr->tte * 900);
	while (!ft_check_die(philo) && !ft_check_max_eat(philo - (philo->id - 1)))
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
	data.philo_ptr = philo;
	if (!philo)
		return (0);
	if (ft_init_thread(&data, philo))
		return (0);
	ft_destroy(&data);
	free(philo);
}
