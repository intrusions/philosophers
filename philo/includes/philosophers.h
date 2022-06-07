/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:09:20 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/08 00:49:10 by jucheval         ###   ########.fr       */
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
	struct s_philo	*philo_ptr;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosophers_must_eat;
	pthread_mutex_t *fork;
	pthread_mutex_t mutex;
}	t_data;

typedef struct s_philo
{
	struct s_data	*data_ptr;
	int				id;
	long			last_eat;
	int				die;
	pthread_t		philo_thread;
}	t_philo;

// ====================================================================================== //
//                                     Initialization                                     //
// ====================================================================================== //

// Check if all parameters are only int
t_bool	ft_check_arg(int argc, char **argv);
// Fill the global structure with input value, and tcheck if value input are valid
t_bool	ft_fill_data_struct(int argc, char **argv, t_data *data);
// Init a mutex array called fork, in data strucutre
t_bool	ft_init_fork(t_data *data);
// Creat an array of t_philo structure, one index per philo, with informations about eatch philo inside
t_philo	*ft_fill_philo_struct(t_data *data);
// Creat a thread per philo, with ft_loop in function, and mutex t_philo structure in parameters
t_bool	ft_init_thread(t_data *data, t_philo *philo);


// ====================================================================================== //
//                                     About routine                                      //
// ====================================================================================== //

// Principal function about routine of philosophers
void	*ft_loop(t_philo *philo);

// ====================================================================================== //
//                                         Utils                                          //
// ====================================================================================== //

// Convert ascii to int
int		ft_atoi(const char *str);
// Get time in ms
long	ft_get_time(void);

#endif