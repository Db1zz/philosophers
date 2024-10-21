/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:51:20 by gonische          #+#    #+#             */
/*   Updated: 2024/10/21 17:41:15 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	run_philosophers(const t_args *args)
{
	const size_t	arrs_size = args->number_of_philosophers;
	t_fork			forks[arrs_size];
	t_philosopher	philosophers[arrs_size];

	if (!init_forks(forks, arrs_size))
		return ;
	if (!create_philosophers(philosophers, forks, arrs_size, args))
		return ;
}

int main(int argc, char **argv)
{
	struct t_args args;

	if (!init_args(argc, argv, &args))
		return (EXIT_FAILURE);
	run_philosophers(&args);
	return (EXIT_SUCCESS);
}
