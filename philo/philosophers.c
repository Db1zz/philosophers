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
	if (philo->timers.tsince_last_meal >= philo->args->time_to_die)
	{
		philo->state = E_STATE_DIED;
		*philo->is_died = true;
	}
	return (*philo->is_died);
}

void	wait_philosophers_to_finish(t_philosopher philo[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

bool	create_philosophers(t_philosopher philos[], t_fork forks[],
							size_t size, const t_args *args)
{
	size_t	i;
	bool	is_died;
	pthread_mutex_t	print_mutex;

	pthread_mutex_init(&print_mutex, NULL);	
	i = 0;
	is_died = false;
	while (i < size)
	{
		philos[i].id = i + 1;
		philos[i].is_died = &is_died;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % size];
		philos[i].state = E_STATE_THINKING;
		philos[i].eat_times = 0;
		philos[i].print_mutex = &print_mutex;
		philos[i].args = args;
		pthread_create(&philos[i].thread, NULL, philosopher_routine, &philos[i]);
		i++;
	}
	wait_philosophers_to_finish(philos, size);
	pthread_mutex_destroy(&print_mutex);
	return (true);
}

void	*philosopher_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)philosopher;
	init_time(&philo->timers);
	while (!(*philo->is_died))
	{
		print_state(philo);
		while (!is_died(philo) && check_update_state(philo))
			update_time(&philo->timers);
	}
	if (philo->state == E_STATE_DIED)
		print_state(philo);
	return (NULL);
}
