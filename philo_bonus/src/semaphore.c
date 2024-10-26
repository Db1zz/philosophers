/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:03:24 by gonische          #+#    #+#             */
/*   Updated: 2024/10/25 19:37:48 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	open_semaphore(t_sem_data *sem_p, char *sem_name, int sem_size)
{
	const char	*msg_err_issuer = "open_semaphore Error:";
 
	if (sem_p == NULL)
	{
		printf("%s sem_p is NULL\n", msg_err_issuer);
		return (false);
	}
	if (sem_name == NULL)
	{
		printf("%s sem_name is NULL\n", msg_err_issuer);
		return (false);
	}
	if (sem_size < 0)
	{
		printf("%s sem_size cannot be < 0\n", msg_err_issuer);
		return (false); 
	}
	sem_p->sem = sem_open(sem_name, O_CREAT, O_RDWR, sem_size);
	if (sem_p == NULL)
	{
		printf("%s cannot open semaphore\n", msg_err_issuer);
		return (false);
	}
	sem_p->name = sem_name;
	return (true);
}

bool	close_semaphore(t_sem_data *sem_p)
{
	const char	*msg_err_issuer = "close_semaphore Error:";

	if (sem_p == NULL)
	{
		printf("%s sem_p is NULL", msg_err_issuer);
		return (false);
	}
	if (sem_close(sem_p->sem) != 0)
	{
		printf("%s sem_close failed\n", msg_err_issuer);
		return (false);
	}
	if (sem_unlink(sem_p->name) != 0)
	{
		printf("%s sem_unlink failed\n", msg_err_issuer);
		return (false);
	}
	return (true);
}

bool	init_semaphores(t_sem_data *forks_sem, size_t size, 
						t_sem_data *global_sem)
{
	if (!open_semaphore(forks_sem, "_philo_forks_pull_sem_", 1))
		return (false);
	if (!open_semaphore(global_sem, "_philo_global_sem_", 1))
	{
		close_semaphore(forks_sem);
		return (false);
	}
	return (true);
}

void	destroy_semaphores(t_sem_data *forks_sem, t_sem_data *global_sem)
{
	close_semaphore(forks_sem);
	close_semaphore(global_sem);
}
