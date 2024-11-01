/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:48:35 by gonische          #+#    #+#             */
/*   Updated: 2024/11/02 00:03:44 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_process_data(t_process *pdata)
{
	pdata->print_sem = NULL;
	pdata->fork_sem = NULL;
	pdata->global_sem = NULL;
	pdata->exit_status = -1;
}

int	main(int argc, char **argv)
{
	t_process	pdata;

	init_process_data(&pdata);
	if (!parse_args(argc, argv, &pdata.args))
		return (EXIT_FAILURE);
	unlink_semaphores();
	if (!open_semaphores(&pdata))
		return (EXIT_FAILURE);
	run_philosophers(&pdata);
	cleanup_semaphores(&pdata);
	unlink_semaphores();
	return (EXIT_SUCCESS);
}
