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
#include <stdio.h>

bool	is_died(t_philosopher *philo)
{
	update_time(&philo->meal_time);
	sem_wait(philo->pdata->global_sem.sem);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		philo->state = E_STATE_DIED;
		if (!philo->pdata->exit_status)
			print_state(philo);
		philo->pdata->exit_status = true;
	}
	sem_post(philo->pdata->global_sem.sem);
	return (philo->pdata->exit_status);
}

static bool	is_philo_done_eating(const t_philosopher *philo)
{
	return (philo->pdata->args.arguments_given == MAX_ARGS_AMOUNT
		&& philo->meal_counter == philo->pdata->args.num_eat_cycles);
}

static bool	check_exit_status(const t_philosopher *philo)
{
	bool	exit_status;

	sem_wait(philo->pdata->global_sem.sem);
	exit_status = philo->pdata->exit_status;
	sem_post(philo->pdata->global_sem.sem);
	return (exit_status);
}

void	init_philosopher(t_philosopher philos[], size_t size,
			t_sem_data *forks_pull, t_process *data)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].state = E_STATE_THINKING;
		philos[i].meal_counter = 0;
		philos[i].pdata = data;
		philos[i].forks_pull = forks_pull;
		i++;
	}
}

void	philosopher_routine(t_philosopher *philo)
{
	init_time(&philo->meal_time);
	init_time(&philo->timestamp);
	while (!check_exit_status(philo) && !is_philo_done_eating(philo))
	{
		sem_wait(philo->pdata->global_sem.sem);
		print_state(philo);
		sem_post(philo->pdata->global_sem.sem);
		while (check_update_state(philo));
	}
}
