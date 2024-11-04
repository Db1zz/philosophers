/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:09:58 by gonische          #+#    #+#             */
/*   Updated: 2024/11/04 11:57:13 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "time.h"

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/wait.h>

# ifndef __USE_POSIX
#  define __USE_POSIX 0
# endif // __USE_POSIX
# include <signal.h>

# define MAX_ARR_SIZE 200
# define MIN_ARGS_AMOUNT 5
# define MAX_ARGS_AMOUNT 6

# define FORK_SEM_NAME "_PHILO_FORK_SEM_"
# define GLOBAL_SEM_NAME "_PHILO_GLOBAL_SEM_"
# define PRINT_SEM_NAME "_PHILO_PRINT_SEM_"

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
	sem_t	*print_sem;
	sem_t	*fork_sem;
	pid_t	pids[MAX_ARR_SIZE];
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
int		ft_atoi(const char *str);
void	reopen_semaphores(t_process *pdata);

// Semaphores
bool	open_semaphore(sem_t **sem, char *sem_name, int sem_size);
void	close_semaphore(sem_t *sem);
bool	open_semaphores(t_process *pdata);
void	cleanup_semaphores(t_process *pdata);
void	unlink_semaphores(void);

// Philosophers function
void	run_philosophers(t_process *pdata);
void	philosopher_routine(t_philosopher *philo);

// Forks
void	take_forks(t_philosopher *philo);
void	put_forks(t_philosopher *philo);

// States
void	check_update_state(t_philosopher *philo);
void	print_state(t_philosopher *philo);

#endif	// PHILOSOPHERS_H
