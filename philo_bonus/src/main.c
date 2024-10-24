/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:51:20 by gonische          #+#    #+#             */
/*   Updated: 2024/10/24 15:53:46 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_philosophers_to_finish(t_philosopher philo[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

static void	run_philosophers(t_process *pdata)
{
	const size_t	size = pdata->args.number_of_philosophers;
	t_philosopher	philosophers[MAX_ARR_SIZE];
	t_sem_data		forks_pull;

	if (!open_semaphore(&forks_pull, "_philo_forks_pull_sem_", size))
		return ;
	init_philosopher(philosophers, size, &forks_pull, pdata);
	
	wait_philosophers_to_finish(philosophers, size);
	close_semaphore(&forks_pull);
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
