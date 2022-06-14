/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucheval <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:09:20 by jucheval          #+#    #+#             */
/*   Updated: 2022/06/14 14:31:20 by jucheval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// ========================================================================= //
//                                   Library                                 //
// ========================================================================= //

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stddef.h>

// ========================================================================= //
//                                   Define                                  //
// ========================================================================= //

# define INT_MAX 2147483647
# define SLEEP 1
# define EAT 2
# define THINK 3
# define LOCK_FORK 4
# define DIE 5

// ========================================================================= //
//                                 Define Color                              //
// ========================================================================= //

# define PINK "\033[95m"
# define END "\033[0m"
# define YELLOW "\033[93m"
# define RED "\033[91m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"

// ========================================================================= //
//                                   Typedef                                 //
// ========================================================================= //

typedef int	t_bool;

// ========================================================================= //
//                                 Strucutre                                 //
// ========================================================================= //

typedef struct s_data
{
	struct s_philo	*philo_ptr;
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				max_eat;
	long			time;
	int				die;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex;
	pthread_mutex_t	check_eat;
	pthread_mutex_t	check_die;
}	t_data;

typedef struct s_philo
{
	struct s_data	*data_ptr;
	int				id;
	int				nb_meal;
	long			last_eat;
	pthread_t		philo_thread;
}	t_philo;

// ========================================================================= //
//                               Initialization                              //
// ========================================================================= //

// Check if all parameters are only int
t_bool	ft_check_arg(int argc, char **argv);
// Fill the data structure with input value, and tcheck if value are valid
t_bool	ft_fill_data_struct(int argc, char **argv, t_data *data);
// Init a mutex array called fork, in data strucutre
t_bool	ft_init_fork_and_check_die(t_data *data);
// Creat an array of t_philo, one per philo, with info about eatch philo inside
t_philo	*ft_fill_philo_struct(t_data *data);
// Creat a thread per philo, with ft_loop in function, and t_philo in params
t_bool	ft_init_thread(t_data *data, t_philo *philo);

// ========================================================================= //
//                                About routine                              //
// ========================================================================= //

// Principal function about routine of philosophers
void	*ft_loop(t_philo *philo);
// Check if all the philosophers have not eaten more times than the max
t_bool	ft_check_eat(t_philo *philo);
// Function to eat
void	ft_eat(t_philo *philo);
// Function to sleep
void	ft_sleep(t_philo *philo, int tts);
// Function to think
void	ft_think(t_philo *data);
//  Function to tcheck if a philo diying
void	ft_death(t_data *data, t_philo *philo);
// Function to print message
void	ft_write(t_philo *philo, int what_message);
// Function to lock fork
void	ft_lock_fork(t_philo *philo);
// Function ton unlock fork
void	ft_unlock_fork(t_philo *philo);
// Function to check die
t_bool	ft_check_die(t_philo *philo);

// ========================================================================= //
//                                    Utils                                  //
// ========================================================================= //

// Convert ascii to int
int		ft_atoi(const char *str);
// Get time in ms
long	ft_get_time(void);
// Function to destroy and free all memory allocated by mutex
void	ft_destroy(t_data *data);
// Function to theck if an input value is smaller than or equal to 0
t_bool	ft_check_input_value(int argc, char **argv, t_data *data);

#endif