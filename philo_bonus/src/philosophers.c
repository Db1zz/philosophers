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

static bool	is_philo_done_eating(const t_philosopher *philo)
{
	return (philo->pdata->args.arguments_given == MAX_ARGS_AMOUNT
		&& philo->meal_counter == philo->pdata->args.num_eat_cycles);
}

static bool	check_exit_status(const t_philosopher *philo)
{
	bool	exit_status;

	sem_wait(philo->pdata->global_sem);
	exit_status = philo->pdata->exit_status;
	sem_post(philo->pdata->global_sem);
	return (exit_status);
}

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
		i++;
	}
}

void	philosopher_routine(t_philosopher *philo)
{
	init_time(&philo->meal_time);
	init_time(&philo->timestamp);
	while (!check_exit_status(philo) && !is_philo_done_eating(philo))
		check_update_state(philo);
}
