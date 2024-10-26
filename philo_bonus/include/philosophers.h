/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:17:40 by gonische          #+#    #+#             */
/*   Updated: 2024/10/26 15:26:17 by gonische         ###   ########.fr       */
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
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/wait.h>
# include <error.h>
# include <string.h>
# include <errno.h>

# define MAX_ARR_SIZE 200
# define MIN_ARGS_AMOUNT 5
# define MAX_ARGS_AMOUNT 6

# define FORK_SEM_NAME "._._PHILO_FORK_SEM_._"
# define GLOBLA_SEM_NAME "._._PHILO_GLOBAL_SEM_._"

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
	t_args		args;
	bool		exit_status;
	sem_t		*global_sem;
	pid_t		pid[MAX_ARR_SIZE];
}	t_process;

typedef struct t_philosopher
{
	size_t		id;
	sem_t		*fork_sem;
	t_state		state;
	int			meal_counter;
	t_time		meal_time;
	t_time		timestamp;
	t_process	*pdata;
}	t_philosopher;

typedef bool	(*t_state_function_p)(t_philosopher *);

// Input handlers
bool	check_arguments(const t_args *args);
bool	init_args(int argc, char **argv, t_args *args);

// Semaphore wrappers
bool	open_semaphore(sem_t **sem, char *sem_name, int sem_size);
bool	destroy_semaphore(sem_t *sem, char *name);
bool	init_semaphores(sem_t **fork_sem, size_t fork_sem_size, sem_t **global_sem);

// Forks
void	take_forks(t_philosopher *philo);
void	put_forks(t_philosopher *philo);

// Philosopher functions
void	init_philosopher(t_philosopher philos[], size_t size, t_process *data);
void	philosopher_routine(t_philosopher *philo);
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