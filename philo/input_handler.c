/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 19:17:32 by gonische          #+#    #+#             */
/*   Updated: 2024/10/20 19:18:45 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define MIN_ARGS_AMOUNT 5
#define MAX_ARGS_AMOUNT 6

bool	check_arguments(const t_args *args)
{
	if (args->number_of_philosophers <= 0)
	{
		printf("Error: Number of philosophers cannot be <= 0\n");
		return (false);
	}
	else if (args->time_to_die < 60 || args->time_to_eat < 60
			|| args->time_to_sleep < 60)
	{
		printf("Error: time_to_die or time_to_eat or time_to_sleep");
		printf(" values cannot be lower than 60ms.\n");
		return (false);
	}
	else if (args->number_of_times_each_philosopher_must_eat < 0)
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
		args->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		args->number_of_times_each_philosopher_must_eat = 0;
	args->arguments_given = argc;
	return (check_arguments(args));
}
