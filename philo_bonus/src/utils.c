/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:00:59 by gonische          #+#    #+#             */
/*   Updated: 2024/11/04 11:56:19 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	neg;

	result = 0;
	i = 0;
	neg = 1;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
		result = (result * 10) + (str[i++] - 48);
	return (result * neg);
}

void	reopen_semaphores(t_process *pdata)
{
	sem_close(pdata->fork_sem);
	sem_close(pdata->global_sem);
	sem_close(pdata->print_sem);
	pdata->fork_sem = sem_open(FORK_SEM_NAME, 0);
	pdata->global_sem = sem_open(GLOBAL_SEM_NAME, 0);
	pdata->print_sem = sem_open(PRINT_SEM_NAME, 0);
}
