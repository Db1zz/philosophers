/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:02:44 by gonische          #+#    #+#             */
/*   Updated: 2024/10/28 15:28:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	exit_on_death(t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	update_time(&philo->meal_time);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		philo->state = E_STATE_DIED;
		print_state(philo);
		exit(EXIT_SUCCESS);
	}
	sem_post(philo->pdata->global_sem);
}

static void	is_philo_done_eating(const t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	if (philo->pdata->args.arguments_given == MAX_ARGS_AMOUNT
		&& philo->meal_counter == philo->pdata->args.num_eat_cycles)
	{
		exit(EXIT_SUCCESS);
	}
	sem_post(philo->pdata->global_sem);
}

void	*monitor_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	while (true)
	{
		is_philo_done_eating(philo);
		exit_on_death(philo);
		usleep(1000);
	}
	return (NULL);
}
