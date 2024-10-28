/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:03:24 by gonische          #+#    #+#             */
/*   Updated: 2024/10/28 14:11:25 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	open_semaphore(sem_t **sem, char *sem_name, int sem_size)
{
	const char	*msg_err_issuer = "open_semaphore Error:";

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
	*sem = sem_open(sem_name, O_CREAT, 0644, sem_size);
	if (*sem == NULL)
	{
		printf("%s cannot open semaphore\n", msg_err_issuer);
		return (false);
	}
	return (true);
}

void	unlink_semaphores(void)
{
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(GLOBLA_SEM_NAME);
}

bool	destroy_semaphore(sem_t *sem, char *name)
{
	const char	*msg_err_issuer = "close_semaphore Error:";

	if (sem_close(sem))
	{
		printf("%s sem_close failed\n", msg_err_issuer);
		return (false);
	}
	if (sem_unlink(name) != 0)
	{
		printf("%s sem_unlink failed\n", msg_err_issuer);
		return (false);
	}
	return (true);
}

bool	init_semaphores(sem_t **fork_sem, size_t fork_sem_size,
			sem_t **global_sem)
{
	if (!open_semaphore(fork_sem, FORK_SEM_NAME, fork_sem_size))
		return (false);
	if (!open_semaphore(global_sem, GLOBLA_SEM_NAME, 1))
	{
		destroy_semaphore(*fork_sem, FORK_SEM_NAME);
		return (false);
	}
	return (true);
}
