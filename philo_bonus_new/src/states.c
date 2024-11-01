/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:00:24 by gonische          #+#    #+#             */
/*   Updated: 2024/11/02 00:13:06 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	state_thinking(t_philosopher *philo)
{
	take_forks(philo);
	sem_wait(philo->pdata->global_sem);
	philo->state = E_STATE_EATING;
	sem_post(philo->pdata->global_sem);
}

static void	state_eating(t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	update_time(&philo->meal_time);
	philo->meal_time.time = 0;
	philo->meal_counter += 1;
	philo->state = E_STATE_SLEEPING;
	sem_post(philo->pdata->global_sem);
	ft_sleep(philo->pdata->args.time_to_eat);
	put_forks(philo);
}

static void	state_sleeping(t_philosopher *philo)
{
	ft_sleep(philo->pdata->args.time_to_sleep);
	sem_wait(philo->pdata->global_sem);
	philo->state = E_STATE_THINKING;
	sem_post(philo->pdata->global_sem);
}

void	check_update_state(t_philosopher *philo)
{
	static const t_state_function_p	functions[] = {
		state_thinking,
		state_eating,
		state_sleeping
	};

	sem_wait(philo->pdata->print_sem);
	print_state(philo);
	sem_post(philo->pdata->print_sem);
	functions[(int)philo->state](philo);
}

void	print_state(t_philosopher *philo)
{
	int64_t	t;

	update_time(&philo->timestamp);
	t = philo->timestamp.time;
	if (philo->state == E_STATE_EATING)
	{
		printf("%lu %zu has taken a fork\n", t, philo->id);
		printf("%lu %zu is eating\n", t, philo->id);
	}
	else if (philo->state == E_STATE_SLEEPING)
		printf("%lu %zu is sleeping\n", t, philo->id);
	else if (philo->state == E_STATE_THINKING)
		printf("%lu %zu is thinking\n", t, philo->id);
	if (philo->state == E_STATE_DIED)
		printf("%lu %zu died\n", t, philo->id);
}
