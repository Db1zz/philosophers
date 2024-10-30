/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:01:04 by gonische          #+#    #+#             */
/*   Updated: 2024/10/30 15:40:02 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	state_thinking(t_philosopher *philo)
{
	take_forks(philo);
	sem_wait(philo->pdata->global_sem);
	philo->state = E_STATE_EATING;
	sem_post(philo->pdata->global_sem);
}

void	state_eating(t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	update_time(&philo->meal_time);
	philo->meal_time.time = 0;
	philo->meal_counter++;
	sem_post(philo->pdata->global_sem);
	ft_sleep(philo->pdata->args.time_to_eat);
	put_forks(philo);
	sem_wait(philo->pdata->global_sem);
	philo->state = E_STATE_SLEEPING;
	sem_post(philo->pdata->global_sem);
}

void	state_sleeping(t_philosopher *philo)
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

	sem_wait(philo->pdata->global_sem);
	print_state(philo);
	sem_post(philo->pdata->global_sem);
	functions[(int)philo->state](philo);
}

// void	print_state(t_philosopher *philo)
// {
// 	int64_t	t;

// 	if (philo->pdata->exit_status)
// 		return ;
// 	update_time(&philo->timestamp);
// 	t = philo->timestamp.time;
// 	if (philo->state == E_STATE_EATING)
// 	{
// 		printf("T[%lu] philo[%zu] has taken a fork\n", t, philo->id);
// 		printf("T[%lu] philo[%zu] is eating (´ᵔ⤙ᵔ`)\n", t, philo->id);
// 	}
// 	else if (philo->state == E_STATE_SLEEPING)
// 		printf("T[%lu] philo[%zu] is sleeping (∪｡∪)｡｡｡zzZ\n", t, philo->id);
// 	else if (philo->state == E_STATE_THINKING)
// 		printf("T[%lu] philo[%zu] is thinking (＃＞＜)\n", t, philo->id);
// 	if (philo->state == E_STATE_DIED)
// 		printf("T[%lu] philo[%zu] died ٩(× ×)۶\n", t, philo->id);
// }

void	print_state(t_philosopher *philo)
{
	int64_t	t;

	if (philo->pdata->exit_status > -1)
		return ;
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
