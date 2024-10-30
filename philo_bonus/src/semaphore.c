/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:03:24 by gonische          #+#    #+#             */
/*   Updated: 2024/10/30 16:30:44 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_semaphore(sem_t **sem, char *sem_name, int sem_size)
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
	*sem = sem_open(sem_name, O_CREAT, S_IRWXU, sem_size);
	if (*sem == NULL)
	{
		printf("%s cannot open semaphore\n", msg_err_issuer);
		return (false);
	}
	return (true);
}

void	destroy_semaphore(sem_t *sem, char *name)
{
	const char	*msg_err_issuer = "close_semaphore Error:";

	if (sem_close(sem))
		printf("%s sem_close failed\n", msg_err_issuer);
	if (sem_unlink(name))
		printf("%s sem_unlink failed\n", msg_err_issuer);
}

void	cleanup_semaphores(sem_t *fork_sem, sem_t *global_sem)
{
	if (fork_sem)
		destroy_semaphore(fork_sem, FORK_SEM_NAME);
	if (global_sem)
		destroy_semaphore(global_sem, GLOBLA_SEM_NAME);
}

bool	init_semaphores(sem_t **fork_sem, size_t fork_sem_size,
			sem_t **global_sem)
{
	if (!init_semaphore(fork_sem, FORK_SEM_NAME, fork_sem_size))
		return (false);
	if (!init_semaphore(global_sem, GLOBLA_SEM_NAME, 1))
	{
		cleanup_semaphores(*fork_sem, NULL);
		return (false);
	}
	return (true);
}

void	unlink_semaphores(void)
{
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(GLOBLA_SEM_NAME);
}
