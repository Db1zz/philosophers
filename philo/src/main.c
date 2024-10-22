/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:51:20 by gonische          #+#    #+#             */
/*   Updated: 2024/10/22 14:48:35 by gonische         ###   ########.fr       */
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
	t_fork			forks[MAX_ARR_SIZE];
	t_philosopher	philosophers[MAX_ARR_SIZE];

	if (!init_forks(forks, size))
		return ;
	if (!create_philosophers(philosophers, forks, size, pdata))
		return ;
	wait_philosophers_to_finish(philosophers, size);
}

static void	init_mutexes(t_process *pdata)
{
	pthread_mutex_init(&pdata->global_mutex, NULL);
	pthread_mutex_init(&pdata->print_mutex, NULL);
}

static void	destroy_mutexes(t_process *pdata)
{
	pthread_mutex_destroy(&pdata->global_mutex);
	pthread_mutex_destroy(&pdata->print_mutex);
}

int	main(int argc, char **argv)
{
	t_process	pdata;

	if (!init_args(argc, argv, &pdata.args))
		return (EXIT_FAILURE);
	pdata.exit_status = false;
	init_mutexes(&pdata);
	run_philosophers(&pdata);
	destroy_mutexes(&pdata);
	return (EXIT_SUCCESS);
}
