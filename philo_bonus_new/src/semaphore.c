/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:26:21 by gonische          #+#    #+#             */
/*   Updated: 2024/11/01 15:01:04 by gonische         ###   ########.fr       */
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
	*sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, sem_size);
	if (*sem == NULL)
	{
		printf("%s cannot open semaphore\n", msg_err_issuer);
		return (false);
	}
	return (true);
}

void	close_semaphore(sem_t *sem)
{
	const char	*msg_err_issuer = "close_semaphore Error:";

	if (sem_close(sem))
		printf("%s sem_close failed\n", msg_err_issuer);
}

bool	open_semaphores(t_process *pdata)
{
	const size_t	fork_sem_size = pdata->args.number_of_philosophers;

	if (!open_semaphore(&pdata->fork_sem, FORK_SEM_NAME, fork_sem_size))
		return (false);
	if (!open_semaphore(&pdata->global_sem, GLOBAL_SEM_NAME, 1))
	{
		cleanup_semaphores(pdata);
		unlink_semaphores();
		return (false);
	}
	return (true);
}

void	cleanup_semaphores(t_process *pdata)
{
	if (pdata->fork_sem)
		close_semaphore(pdata->fork_sem);
	if (pdata->global_sem)
		close_semaphore(pdata->global_sem);
}

void	unlink_semaphores(void)
{
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(GLOBAL_SEM_NAME);
}
