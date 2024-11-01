/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:23:27 by gonische          #+#    #+#             */
/*   Updated: 2024/11/01 15:34:51 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philosopher(t_philosopher *philo, t_process *pdata)
{
	philo->id = 0;
	philo->pdata = pdata;
	philo->state = E_STATE_THINKING;
	philo->meal_counter = 0;
	if (pdata->args.arguments_given == MAX_ARGS_AMOUNT)
		philo->is_meals_counter_needed = true;
	init_time(&philo->timestamp);
	init_time(&philo->meal_time);
}

static int	create_philosophers(t_philosopher *philo)
{
	int			i;
	t_process	*pdata;

	i = 0;
	pdata = philo->pdata;
	while (i < pdata->args.number_of_philosophers)
	{
		philo->id = i + 1;
		pdata->pids[i] = fork();
		if (pdata->pids[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static void	kill_processes(t_process *pdata)
{
	int	i;

	i = 0;
	while (i < pdata->args.number_of_philosophers)
	{
		kill(pdata->pids[i], SIGKILL);
		i++;
	}
}

static void	wait_philosophers_to_finish(t_process *pdata)
{
	int	status;
	int	i;

	i = 0;
	while (i < pdata->args.number_of_philosophers)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status == EXIT_FAILURE)
		{
			kill_processes(pdata);
			return ;
		}
		i++;
	}
}

void	run_philosophers(t_process *pdata)
{
	t_philosopher	philo;

	init_philosopher(&philo, pdata);
	if (create_philosophers(&philo) == 0)
		philosopher_routine(&philo);
	else
		wait_philosophers_to_finish(pdata);
}
