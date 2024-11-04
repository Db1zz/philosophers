/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:00:38 by gonische          #+#    #+#             */
/*   Updated: 2024/11/04 12:32:57 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philosopher *philo)
{
	if (philo->pdata->args.number_of_philosophers % 2)
		ft_sleep(1);
	sem_wait(philo->pdata->fork_sem);
	sem_wait(philo->pdata->fork_sem);
}

void	put_forks(t_philosopher *philo)
{
	sem_post(philo->pdata->fork_sem);
	sem_post(philo->pdata->fork_sem);
}
