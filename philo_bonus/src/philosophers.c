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
	pthread_mutex_lock(&philo->pdata->global_mutex);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		philo->state = E_STATE_DIED;
		if (!philo->pdata->exit_status)
			print_state(philo);
		philo->pdata->exit_status = true;
	}
	pthread_mutex_unlock(&philo->pdata->global_mutex);
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

	pthread_mutex_lock(&philo->pdata->global_mutex);
	exit_status = philo->pdata->exit_status;
	pthread_mutex_unlock(&philo->pdata->global_mutex);
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

bool	create_philosophers(t_philosopher *philos[], t_process *pdata, size_t size)
{
	size_t	i;

	i = -1;
	// First pack
	while (++i < size)
	{
		if (i + 1 % 2 == 0)
			continue ;
		pdata->pid[i] = fork();
		if (pdata->pid[i] == 0)
		{
			philosopher_routine(philos[i]);
			return (true);
		}
	}
	i = -1;
	// Second pack
	while (++i < size)
	{
		if (i + 1 % 2 != 0)
			continue ;
		pdata->pid[i] = fork();
		if (pdata->pid[i] == 0)
		{
			philosopher_routine(philos[i]);
			return (true);
		}
	}
	return (false);
}

/*
	tldr: this shitty norminette doesn't allow me to write pretty code :(
	while (check_update_state(philo) && !is_died(philo));
*/
void	philosopher_routine(t_philosopher *philo)
{
	init_time(&philo->meal_time);
	init_time(&philo->timestamp);
	while (!check_exit_status(philo) && !is_philo_done_eating(philo))
	{
		pthread_mutex_lock(&philo->pdata->global_mutex);
		print_state(philo);
		pthread_mutex_unlock(&philo->pdata->global_mutex);
		while (check_update_state(philo))
		{
			if (is_died(philo))
				break ;
		}
	}
	return (NULL);
}
