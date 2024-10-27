/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:51:20 by gonische          #+#    #+#             */
/*   Updated: 2024/10/27 11:44:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_philosophers(t_philosopher philos[],
			t_process *pdata, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pdata->pid[i] = fork();
		if (pdata->pid[i] == 0)
		{
			philos[i].fork_sem = sem_open(FORK_SEM_NAME, 0);
			philos[i].pdata->global_sem = sem_open(GLOBLA_SEM_NAME, 0);
			if (!philos[i].fork_sem || !philos[i].pdata->global_sem)
				return (1);
			philosopher_routine(&philos[i]);
			sem_close(philos[i].fork_sem);
			sem_close(philos[i].pdata->global_sem);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	run_philosophers(t_process *pdata)
{
	const size_t	size = pdata->args.number_of_philosophers;
	t_philosopher	philosophers[MAX_ARR_SIZE];
	sem_t			*fork_sem;

	if (!init_semaphores(&fork_sem, size, &(pdata->global_sem)))
		return ;
	init_philosopher(philosophers, size, pdata);
	if (create_philosophers(philosophers, pdata, size))
		exit(EXIT_SUCCESS);
	for (int i = 0; i < size; i++)
		waitpid(pdata->pid[i], NULL, 0);
	destroy_semaphore(pdata->global_sem, FORK_SEM_NAME);
	destroy_semaphore(pdata->global_sem, GLOBLA_SEM_NAME);
}

int	main(int argc, char **argv)
{
	t_process	pdata;

	if (!init_args(argc, argv, &pdata.args))
		return (EXIT_FAILURE);
	unlink_semaphores();
	pdata.exit_status = false;
	run_philosophers(&pdata);
	return (EXIT_SUCCESS);
}
