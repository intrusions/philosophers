/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xel <xel@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:09:20 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/06 19:17:01 by xel              ###   ########.fr       */
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
 
// ====================================================================================== //
//                                         Typedef                                        //
// ====================================================================================== //

typedef int t_bool;

// ====================================================================================== //
//                                        Stucture                                        //
// ====================================================================================== //

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

// ====================================================================================== //
//                                     Initialization                                     //
// ====================================================================================== //

// Check if all parameters are valid
t_bool	ft_check_arg(int argc, char **argv);
// Fill the global structure with input value
t_bool	ft_fill_global_struct(int argc, char **argv, t_data *data);
// Creat a thread per philo, with ft_routine in function, and mutex in parameters
t_bool	ft_init_thread(t_data *data, t_philo *philo, pthread_mutex_t *mutex);

// ====================================================================================== //
//                                         Utils                                          //
// ====================================================================================== //

int		ft_atoi(const char *str);

#endif