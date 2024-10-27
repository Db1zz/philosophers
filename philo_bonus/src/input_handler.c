/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:17:32 by gonische          #+#    #+#             */
/*   Updated: 2024/10/27 14:22:29 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	check_arguments(const t_args *args)
{
	if (args->number_of_philosophers < 1 || args->number_of_philosophers > 200)
	{
		printf("Error: Number of philosophers should be in range 1 - 200\n");
		return (false);
	}
	else if (args->time_to_die < 60 || args->time_to_eat < 60
		|| args->time_to_sleep < 60)
	{
		printf("Error: time_to_die or time_to_eat or time_to_sleep");
		printf(" values cannot be lower than 60ms and greater int64_t.\n");
		return (false);
	}
	else if (args->num_eat_cycles < 0)
	{
		printf("Error: number_of_times_each_philosopher_must_eat is < 0\n");
		return (false);
	}
	return (true);
}

bool	init_args(int argc, char **argv, t_args *args)
{
	if (argc != MIN_ARGS_AMOUNT && argc != MAX_ARGS_AMOUNT)
	{
		printf("Error: Incorrect amount of arguments: %d\n", argc);
		return (false);
	}
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == MAX_ARGS_AMOUNT)
		args->num_eat_cycles = ft_atoi(argv[5]);
	else
		args->num_eat_cycles = 0;
	args->arguments_given = argc;
	return (check_arguments(args));
}
