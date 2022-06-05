/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:09:20 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/04 23:43:20 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
typedef struct s_data
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosophers_must_eat;
}	t_data;

typedef struct s_philo
{
	int			id;
	pthread_t	philo_thread;
	int			eat;
	int			think;
	int			sleep;
	int			last_eat;
}	t_philo;



//utils
int		ft_atoi(const char *str);
void	ft_init_struct(t_data *data);
void	ft_fill_struct(int argc, char **argv, t_data *data);

#endif