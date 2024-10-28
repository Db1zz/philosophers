/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:22:36 by gonische          #+#    #+#             */
/*   Updated: 2024/10/28 14:16:00 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_forks(t_fork forks[], size_t arr_size)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < arr_size)
	{
		forks[i].is_taken = false;
		if ((i + 1) % 2 == 0)
			forks[i].was_used_by = (i + 1) % arr_size;
		else
			forks[i].was_used_by = -1;
		status = pthread_mutex_init(&forks[i].mutex, NULL);
		if (status != 0)
		{
			printf("Error: Insufficient amout of rescourses to init forks\n");
			return (false);
		}
		i++;
	}
	return (true);
}

bool	set_fork_status(t_philosopher *philo, t_fork *fork, bool to_take)
{
	bool	status;

	status = false;
	pthread_mutex_lock(&fork->mutex);
	if (philo->id != fork->was_used_by && fork->is_taken != to_take)
	{
		fork->is_taken = to_take;
		status = true;
	}
	pthread_mutex_unlock(&fork->mutex);
	return (status);
}

bool	acquire_release_forks(t_philosopher *philo, bool to_acquire)
{
	if (!set_fork_status(philo, philo->left_fork, to_acquire))
		return (false);
	if (!set_fork_status(philo, philo->right_fork, to_acquire))
	{
		set_fork_status(philo, philo->left_fork, !to_acquire);
		return (false);
	}
	if (!to_acquire)
	{
		philo->left_fork->was_used_by = philo->id;
		philo->right_fork->was_used_by = philo->id;
	}
	return (true);
}
