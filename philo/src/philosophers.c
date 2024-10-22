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

static bool	is_finished_eating(const t_philosopher *philo)
{
	return (philo->pdata->args.arguments_given == MAX_ARGS_AMOUNT
		&& philo->meal_counter == philo->pdata->args.num_eat_cycles);
}

bool	create_philosophers(t_philosopher philos[], t_fork forks[],
							size_t size, t_process *data)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % size];
		philos[i].state = E_STATE_THINKING;
		philos[i].meal_counter = 0;
		philos[i].pdata = data;
		if (pthread_create(&philos[i].thread, NULL,
				philosopher_routine, &philos[i]))
		{
			printf("Error: pthread_create failed\n");
			return (false);
		}
		i++;
	}
	return (true);
}

/*
	tldr: this shitty norminette doesn't allow me to write pretty code :(
	while (check_update_state(philo) && !is_died(philo));
*/
void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	init_time(&philo->meal_time);
	init_time(&philo->timestamp);
	while (!philo->pdata->exit_status && !is_finished_eating(philo))
	{
		print_state(philo);
		while (check_update_state(philo))
		{
			if (is_died(philo))
				break ;
		}
	}
	return (NULL);
}