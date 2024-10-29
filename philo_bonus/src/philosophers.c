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

void	init_philosopher(t_philosopher philos[], size_t size, t_process *data)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].state = E_STATE_THINKING;
		philos[i].meal_counter = 0;
		philos[i].pdata = data;
		init_time(&philos[i].meal_time);
		init_time(&philos[i].timestamp);
		i++;
	}
}

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

void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor_routine, philo))
	{
		printf("Error: cannot create monitor thread\n");
		exit(EXIT_FAILURE);
	}
	while (!check_exit_status(philo))
		check_update_state(philo);
	pthread_join(thread, NULL);
}
