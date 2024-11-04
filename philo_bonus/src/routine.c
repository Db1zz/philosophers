/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 23:34:53 by gonische          #+#    #+#             */
/*   Updated: 2024/11/04 12:35:41 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	is_dead(t_philosopher *philo)
{
	sem_wait(philo->pdata->global_sem);
	update_time(&philo->meal_time);
	if (philo->meal_time.time >= philo->pdata->args.time_to_die)
	{
		update_time(&philo->timestamp);
		philo->pdata->exit_status = EXIT_FAILURE;
		philo->state = E_STATE_DIED;
		sem_post(philo->pdata->global_sem);
		sem_wait(philo->pdata->print_sem);
		printf("%lu %zu died\n", philo->timestamp.time, philo->id);
		return (true);
	}
	sem_post(philo->pdata->global_sem);
	return (false);
}

static bool	can_exit(t_process *pdata)
{
	bool	status;

	status = false;
	sem_wait(pdata->global_sem);
	if (pdata->exit_status > -1)
		status = true;
	sem_post(pdata->global_sem);
	return (status);
}

static void	*monitor_routine(void *philosopher)
{
	t_philosopher	*philo;

	philo = philosopher;
	while (!is_dead(philo) && !can_exit(philo->pdata))
		usleep(1000);
	return (NULL);
}

static bool	is_done_eating(t_philosopher *philo)
{
	if (!philo->is_meals_counter_needed)
		return (false);
	sem_wait(philo->pdata->global_sem);
	if (philo->meal_counter >= philo->pdata->args.num_eat_cycles)
	{
		philo->pdata->exit_status = EXIT_SUCCESS;
		sem_post(philo->pdata->global_sem);
		return (true);
	}
	sem_post(philo->pdata->global_sem);
	return (false);
}

/*
	Unfortunately, but we cannot achieve perfect synhronization
	between philo and monitor. The reason covers in allowed functions,
	and 42 doesn't allow to use nameless semaphores. So stupid ;(
*/
void	philosopher_routine(t_philosopher *philo)
{
	pthread_t	monitor_thread;

	reopen_semaphores(philo->pdata);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, philo))
	{
		printf("Error: cannot create monitor_thread\n");
		exit(EXIT_FAILURE);
	}
	if (philo->pdata->args.number_of_philosophers == 1)
	{
		pthread_join(monitor_thread, NULL);
		exit(philo->pdata->exit_status);
	}
	while (!can_exit(philo->pdata) && !is_done_eating(philo))
		check_update_state(philo);
	pthread_join(monitor_thread, NULL);
	cleanup_semaphores(philo->pdata);
	exit(philo->pdata->exit_status);
}
