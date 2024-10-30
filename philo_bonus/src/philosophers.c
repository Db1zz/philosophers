/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:49:26 by gonische          #+#    #+#             */
/*   Updated: 2024/10/21 12:50:29 by gonische         ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_exit_status(t_philosopher *philo)
{
	bool	status;

	status = false;
	sem_wait(philo->pdata->global_sem);
	if (philo->pdata->exit_status > -1)
		status = true;
	sem_post(philo->pdata->global_sem);
	return (status);
}

void	init_philosopher(t_philosopher philos[], size_t size,
			t_process *data, sem_t *fork_sem)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].state = E_STATE_THINKING;
		philos[i].meal_counter = 0;
		philos[i].pdata = data;
		philos[i].fork_sem = fork_sem;
		init_time(&philos[i].meal_time);
		init_time(&philos[i].timestamp);
		i++;
	}
}

void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor_routine, philo))
	{
		printf("Error: cannot create monitor thread\n");
		exit(EXIT_FAILURE);
	}
	pthread_detach(thread);
	while (!check_exit_status(philo))
		check_update_state(philo);
}

/*
	Since the child process doesn't inherit descriptors from the parent,
	we have to reopen each semaphore.
*/
void	philosopher_reopen_semaphores(t_philosopher *philo)
{
	sem_close(philo->fork_sem);
	sem_close(philo->pdata->global_sem);
	philo->fork_sem = sem_open(FORK_SEM_NAME, 0);
	philo->pdata->global_sem = sem_open(GLOBLA_SEM_NAME, 0);
}

/*
	равлик)
*/
void	philosopher_exit_routine(t_philosopher *philo)
{
	sem_close(philo->fork_sem);
	sem_close(philo->pdata->global_sem);
	exit(philo->pdata->exit_status);
}
