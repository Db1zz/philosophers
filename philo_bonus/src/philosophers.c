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

void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, monitor_routine, philo))
	{
		printf("Error: cannot create monitor thread\n");
		exit(EXIT_FAILURE);
	}
	pthread_detach(thread);
	while (true)
		check_update_state(philo);
	exit(EXIT_SUCCESS);
}
