/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:17:40 by gonische          #+#    #+#             */
/*   Updated: 2024/10/22 15:00:15 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "time.h"

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>

# define MAX_ARR_SIZE 200
# define MIN_ARGS_AMOUNT 5
# define MAX_ARGS_AMOUNT 6

typedef enum e_state
{
	E_STATE_THINKING,
	E_STATE_EATING,
	E_STATE_SLEEPING,
	E_STATE_DIED,
	E_STATE_COUNT
}	t_state;

typedef struct t_fork
{
	pthread_mutex_t	mutex;
	bool			is_taken;
	size_t			was_used_by;
}	t_fork;

typedef struct t_args
{
	int			number_of_philosophers;
	int64_t		time_to_die;
	int64_t		time_to_eat;
	int64_t		time_to_sleep;
	int			num_eat_cycles;
	size_t		arguments_given;
}	t_args;

typedef struct t_process
{
	t_args			args;
	bool			exit_status;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	global_mutex;
}	t_process;

typedef struct t_philosopher
{
	size_t				id;
	pthread_t			thread;
	t_fork				*left_fork;
	t_fork				*right_fork;
	t_state				state;
	int					meal_counter;
	t_time				meal_time;
	t_time				timestamp;
	t_process			*pdata;
}	t_philosopher;

typedef bool	(*t_state_function_p)(t_philosopher *);

// Input handlers
bool	check_arguments(const t_args *args);
bool	init_args(int argc, char **argv, t_args *args);

// Forks
bool	init_forks(t_fork forks[], size_t arr_size);
bool	set_fork_status(t_philosopher *philo, t_fork *fork, bool to_take);
bool	acquire_release_forks(t_philosopher *philo, bool to_acquire);

// Init functions
bool	init_forks(t_fork forks[], size_t arr_size);

// Philosopher functions
void	*philosopher_routine(void *philosopher);
bool	create_philosophers(t_philosopher philos[], t_fork forks[],
			size_t size, t_process *data);
bool	is_died(t_philosopher *philo);

// State related functions
bool	is_state_thinking(t_philosopher *philo);
bool	is_state_eating(t_philosopher *philo);
bool	is_state_sleeping(t_philosopher *philo);
void	print_state(t_philosopher *philo);
bool	check_update_state(t_philosopher *philo);

// Utility functions
int		ft_atoi(const char *str);
bool	thread_sleep_routine(int64_t ms, bool (*f)(t_philosopher *),
			void *f_d);
#endif // PHILOSOPHERS_H