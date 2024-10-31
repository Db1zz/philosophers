/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:09:58 by gonische          #+#    #+#             */
/*   Updated: 2024/10/31 16:29:10 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include "time.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>

# ifndef __USE_POSIX
#  define __USE_POSIX 0
# endif // __USE_POSIX
# include <signal.h>

# define MAX_ARR_SIZE 200
# define MIN_ARGS_AMOUNT 5
# define MAX_ARGS_AMOUNT 6

# define FORK_SEM_NAME "_PHILO_FORK_SEM_"
# define GLOBLA_SEM_NAME "_PHILO_GLOBAL_SEM_"

typedef enum e_state
{
	E_STATE_THINKING,
	E_STATE_EATING,
	E_STATE_SLEEPING,
	E_STATE_DIED,
	E_STATE_COUNT
}	t_state;

typedef struct t_args
{
	int		number_of_philosophers;
	int64_t	time_to_die;
	int64_t	time_to_eat;
	int64_t	time_to_sleep;
	int		num_eat_cycles;
	size_t	arguments_given;
}	t_args;

typedef struct t_process
{
	t_args	args;
	int		exit_status;
	sem_t	*global_sem;
	sem_t	*exit_sem;
	sem_t	*fork_sem;
	pid_t	pid[MAX_ARR_SIZE];
	
}	t_process;

typedef struct t_philosopher
{
	size_t		id;
	t_state		state;
	int			meal_counter;
	bool		is_meals_counter_needed;
	t_time		meal_time;
	t_time		timestamp;
	t_process	*pdata;
}	t_philosopher;

typedef void	(*t_state_function_p)(t_philosopher *);

// Args pareser
bool	parse_args(int argc, char **argv, t_args *args);

// Timer functions
void	init_time(t_time *time);
void	update_time(t_time *time);
int64_t	get_time(void);
void	ft_sleep(int64_t ms);

// Utility functions
int	ft_atoi(const char *str);

// Semaphores
bool	open_semaphore(sem_t **sem, char *sem_name, int sem_size);
void	destroy_semaphore(sem_t *sem, char *name);
bool	open_semaphores(t_process *pdata);
void	cleanup_semaphores(t_process *pdata);
void	unlink_semaphores(void);

// Philosophers function
void	init_philosopher(t_philosopher *philo, t_process *pdata);

#endif	// PHILOSOPHERS_H
