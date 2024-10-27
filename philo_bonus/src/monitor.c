/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:02:44 by gonische          #+#    #+#             */
/*   Updated: 2024/10/27 11:43:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_died(t_philosopher *philo)
{
	update_time(&philo->meal_time);
	sem_wait(philo->pdata->global_sem);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		philo->state = E_STATE_DIED;
		if (!philo->pdata->exit_status)
			print_state(philo);
		philo->pdata->exit_status = true;
	}
	sem_post(philo->pdata->global_sem);
	return (philo->pdata->exit_status);
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
	while (is_died(philo))
	{
		if (philo->state != perv_state)
		{
			sem_wait(philo->pdata->global_sem);
			print_state(philo);
			sem_post(philo->pdata->global_sem);
			perv_state = philo->state;
		}
		usleep(100);
	}
	return (NULL);
}
