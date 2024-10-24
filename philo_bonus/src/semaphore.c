/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:03:24 by gonische          #+#    #+#             */
/*   Updated: 2024/10/24 12:42:30 by gonische         ###   ########.fr       */
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
	if (sem_unlink(sem_p->sem) != 0)
	{
		printf("%s sem_unlink failed\n", msg_err_issuer);
		return (false);
	}
	return (true);
}


