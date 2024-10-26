/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:56:08 by gonische          #+#    #+#             */
/*   Updated: 2024/10/25 19:36:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <errno.h>
#include <string.h>

void	take_forks(t_philosopher *philo)
{
	int err;
	err = sem_wait(philo->forks_pull->sem);
	if (err)
		printf ("%s\n", strerror(errno));
	err = sem_wait(philo->forks_pull->sem);
	if (err)
		printf ("%s\n", strerror(errno));
}

void	put_forks(t_philosopher *philo)
{
	sem_post(philo->forks_pull->sem);
	sem_post(philo->forks_pull->sem);
}
