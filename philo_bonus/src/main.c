/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:51:20 by gonische          #+#    #+#             */
/*   Updated: 2024/10/25 15:28:35 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// static void	wait_philosophers_to_finish(t_philosopher philo[], size_t size)
// {

// }

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
			philosopher_routine(&philos[i]);
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
	t_sem_data		forks_pull;

	if (!init_semaphores(&forks_pull, size, &pdata->global_sem))
		return ;
	init_philosopher(philosophers, size, &forks_pull, pdata);
	if (create_philosophers(philosophers, pdata, size))
		exit(EXIT_SUCCESS);
	for (int i = 0; i < size; i++)
		waitpid(pdata->pid[i], NULL, 0);
	destroy_semaphores(&forks_pull, &pdata->global_sem);
}

int	main(int argc, char **argv)
{
	t_process	pdata;

	if (!init_args(argc, argv, &pdata.args))
		return (EXIT_FAILURE);
	pdata.exit_status = false;
	run_philosophers(&pdata);
	return (EXIT_SUCCESS);
}
