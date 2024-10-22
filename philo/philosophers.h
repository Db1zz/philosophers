/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:17:40 by gonische          #+#    #+#             */
/*   Updated: 2024/10/21 23:50:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>

typedef enum e_state
{
	E_STATE_THINKING,
	E_STATE_EATING,
	E_STATE_SLEEPING,
	E_STATE_DIED,
	E_STATE_COUNT
}	e_state;

typedef struct t_fork
{
	pthread_mutex_t mutex;
	bool			is_taken;
	int				was_used_by;
}	t_fork;

typedef struct t_args
{
	int			number_of_philosophers;
	uint64_t	time_to_die;
	uint64_t	time_to_eat;
	uint64_t	time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	size_t		arguments_given;
}	t_args;

typedef struct t_time
{
	uint64_t	time;
	uint64_t	pervious;
	uint64_t	diff;
}	t_time;

typedef struct t_philosopher
{
	size_t				id;
	bool				*is_died;
	pthread_t			*thread;
	t_fork				*left_fork;
	t_fork				*right_fork;
	e_state				state;
	size_t				eat_times;
	t_time				meal_time;
	t_time				timestamp;
	pthread_mutex_t		*print_mutex;
	const t_args		*args;
}	t_philosopher;

#define STATE_ARRAY_MAX_INDEX 2
typedef bool (*t_state_function_p)(t_philosopher *);

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
							size_t size, const t_args *args);
void	wait_philosophers_to_finish(t_philosopher philo[], size_t size);
bool	is_died(t_philosopher *philo);

// State related functions
bool	is_state_thinking(t_philosopher *philo);
bool	is_state_eating(t_philosopher *philo);
bool	is_state_sleeping(t_philosopher *philo);
void	print_state(t_philosopher *philo);
bool	check_update_state(t_philosopher *philo);

// Utility functions
int		ft_atoi(const char *str);

#ifndef SLEEP_INTERVAL
#define SLEEP_INTERVAL 100
#endif // SLEEP_INTERVAL

uint64_t	get_time(void);
void		init_time(t_time *time);
void		update_time(t_time *time);
bool	thread_sleep_routine(uint64_t ms, bool (*f)(t_philosopher *), void *f_d);
#endif // PHILOSOPHERS_H