/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:56:08 by gonische          #+#    #+#             */
/*   Updated: 2024/10/29 14:15:25 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	sem_wait(philo->fork_sem);
	if (philo->pdata->args.number_of_philosophers % 2)
		usleep(100);
	sem_wait(philo->fork_sem);
}

void	put_forks(t_philosopher *philo)
{
	sem_post(philo->fork_sem);
	sem_post(philo->fork_sem);
}
