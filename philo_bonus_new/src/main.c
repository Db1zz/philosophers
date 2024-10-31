/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:48:35 by gonische          #+#    #+#             */
/*   Updated: 2024/10/31 16:31:07 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	create_philosopher()
{
	
}

static void	run_philosophers(t_process *pdata)
{
	t_philosopher	philo;
	size_t			philo_id;

	init_philosopher(&philo, pdata);
	
}

static void	init_process_data(t_process *pdata)
{
	pdata->exit_sem = NULL;
	pdata->fork_sem = NULL;
	pdata->global_sem = NULL;
	pdata->exit_status = -1; // - Do we need this?
}

int	main(int argc, char **argv)
{
	t_process		pdata;

	init_process_data(&pdata);
	if (!parse_args(argc, argv, &pdata.args))
		return (EXIT_FAILURE);
	if (!open_semaphores(&pdata))
		return (EXIT_FAILURE);
	run_philosophers(&pdata);
	cleanup_semaphores(&pdata);
	return (EXIT_SUCCESS);
}
