/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:02:44 by gonische          #+#    #+#             */
/*   Updated: 2024/10/29 18:55:24 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool exit_on_death(t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	update_time(&philo->meal_time);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		philo->state = E_STATE_DIED;
		print_state(philo);
		philo->pdata->exit_status = EXIT_FAILURE;
		return (true);
	}
	sem_post(philo->pdata->global_sem);
	return (false);
}

static bool	is_philo_done_eating(const t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	if (philo->pdata->args.arguments_given == MAX_ARGS_AMOUNT
		&& philo->meal_counter == philo->pdata->args.num_eat_cycles
		&& philo->state == E_STATE_SLEEPING)
	{
		philo->pdata->exit_status = EXIT_SUCCESS;
		sem_post(philo->pdata->global_sem);
		return (true);
	}
	sem_post(philo->pdata->global_sem);
	return (false);
}

void	*monitor_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (!is_philo_done_eating(philo) && !exit_on_death(philo))
		usleep(1000);
	return (NULL);
}
