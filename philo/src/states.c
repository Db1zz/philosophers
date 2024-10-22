/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:01:04 by gonische          #+#    #+#             */
/*   Updated: 2024/10/22 17:27:18 by gonische         ###   ########.fr       */
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
	update_time(&philo->meal_time);
	philo->meal_time.time = 0;
	philo->meal_counter++;
	thread_sleep_routine(philo->pdata->args.time_to_eat, NULL, NULL);
	acquire_release_forks(philo, false);
	philo->state = E_STATE_SLEEPING;
	return (false);
}

bool	is_state_sleeping(t_philosopher *philo)
{
	if (philo->state != E_STATE_SLEEPING)
		return (false);
	if (thread_sleep_routine(philo->pdata->args.time_to_sleep, is_died, philo))
		return (false);
	philo->state = E_STATE_THINKING;
	return (false);
}

bool	check_update_state(t_philosopher *philo)
{
	static const t_state_function_p	functions[] = {
		is_state_thinking,
		is_state_eating,
		is_state_sleeping
	};

	if (philo->state >= E_STATE_DIED)
		return (false);
	return (functions[(int)philo->state](philo));
}

void	print_state(t_philosopher *philo)
{
	int64_t	t;

	if (philo->pdata->exit_status)
		return ;
	update_time(&philo->timestamp);
	t = philo->timestamp.time;
	if (philo->state == E_STATE_EATING)
	{
		printf("T[%lu] philo[%zu] has taken a fork\n", t, philo->id);
		printf("T[%lu] philo[%zu] is eating (´ᵔ⤙ᵔ`)\n", t, philo->id);
	}
	else if (philo->state == E_STATE_SLEEPING)
		printf("T[%lu] philo[%zu] is sleeping (∪｡∪)｡｡｡zzZ\n", t, philo->id);
	else if (philo->state == E_STATE_THINKING)
		printf("T[%lu] philo[%zu] is thinking (＃＞＜)\n", t, philo->id);
	if (philo->state == E_STATE_DIED)
		printf("T[%lu] philo[%zu] is died ٩(× ×)۶\n", t, philo->id);
}
