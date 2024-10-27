/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:02:44 by gonische          #+#    #+#             */
/*   Updated: 2024/10/27 14:53:37 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_on_death(t_philosopher *philo)
{
	update_time(&philo->meal_time);
	sem_wait(philo->pdata->global_sem);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		philo->state = E_STATE_DIED;
		print_state(philo);
		exit(EXIT_SUCCESS);
	}
	sem_post(philo->pdata->global_sem);
}

void	*monitor_routine(void *philosopher)
{
	t_philosopher	*philo;
	t_state			perv_state;

	philo = (t_philosopher *)philosopher;
	perv_state = philo->state;
	sem_wait(philo->pdata->global_sem);
	print_state(philo);
	sem_post(philo->pdata->global_sem);
	while (true)
	{
		exit_on_death(philo);
		if (philo->state != perv_state)
		{
			sem_wait(philo->pdata->global_sem);
			print_state(philo);
			sem_post(philo->pdata->global_sem);
			perv_state = philo->state;
		}
		usleep(250);
	}
	return (NULL);
}
