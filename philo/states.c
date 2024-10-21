/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:01:04 by gonische          #+#    #+#             */
/*   Updated: 2024/10/21 18:26:58 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_state_thinking(t_philosopher *philo)
{
	if (philo->state != E_STATE_THINKING)
		return (false);
	if (!acquire_release_forks(philo, true))
		return (true);
	philo->state = E_STATE_EATING;
	return (false);
}

bool	is_state_eating(t_philosopher *philo)
{
	if (philo->state != E_STATE_EATING)
		return (false);
	thread_sleep(philo->args->time_to_eat);
	acquire_release_forks(philo, false);
	update_time(&philo->timers);
	philo->timers.tsince_last_meal = 0;
	philo->state = E_STATE_SLEEPING;
	return (false);
}

bool	is_state_sleeping(t_philosopher *philo)
{
	if (philo->state != E_STATE_SLEEPING)
		return (false);
	thread_sleep(philo->args->time_to_sleep);
	if (philo->timers.tstate < philo->args->time_to_sleep)
		return (true);
	philo->state = E_STATE_THINKING;
	return (false);
}

bool	check_update_state(t_philosopher *philo)
{
	static const t_state_function_p functions[] = {
		is_state_thinking,
		is_state_eating,
		is_state_sleeping
	};

	if (philo->state >= E_STATE_COUNT)
		return (false);
	return (functions[(int)philo->state](philo));
}

void	print_state(t_philosopher *philo)
{
	uint64_t	timestamp;

	timestamp = philo->timers.timestamp;
	pthread_mutex_lock(philo->print_mutex);
	if (philo->state == E_STATE_EATING)
	{
		printf("T[%llu] philosopher[%zu] has taken a fork\n", timestamp, philo->id);
		printf("T[%llu] philosopher[%zu] is eating\n", timestamp, philo->id);
	}
	else if (philo->state == E_STATE_SLEEPING)
		printf("T[%llu] philosopher[%zu] is sleeping\n", timestamp, philo->id);
	else if (philo->state == E_STATE_THINKING)
		printf("T[%llu] philosopher[%zu] is thinking\n", timestamp, philo->id);
	if (philo->state == E_STATE_DIED)
		printf("T[%llu] philosopher[%zu] is died :(\n", timestamp, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}
