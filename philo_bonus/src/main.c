/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:51:20 by gonische          #+#    #+#             */
/*   Updated: 2024/10/29 18:58:06 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philosopher	*create_philosophers(t_philosopher philos[],
			t_process *pdata, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		pdata->pid[i] = fork();
		if (pdata->pid[i] == 0)
			return (&philos[i]);
		i++;
	}
	return (NULL);
}

static void	kill_processes(pid_t pids[], size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		kill(pids[i++], SIGKILL);
}

static void	wait_philos_to_finish(pid_t pids[], size_t size)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < size)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		if (status == EXIT_FAILURE)
		{
			kill_processes(pids, size);
			return ;
		}
		else if (status == EXIT_SUCCESS)
			i++;
	}
}

static void	run_philosophers(t_process *pdata)
{
	const size_t	size = pdata->args.number_of_philosophers;
	t_philosopher	philosophers[MAX_ARR_SIZE];
	t_philosopher	*created_philo;
	sem_t			*fork_sem;

	if (!init_semaphores(&fork_sem, size, &pdata->global_sem))
		return ;
	init_philosopher(philosophers, size, pdata);
	created_philo = create_philosophers(philosophers, pdata, size);
	if (created_philo == NULL)
	{
		wait_philos_to_finish(pdata->pid, size);
		destroy_semaphore(fork_sem, FORK_SEM_NAME);
		destroy_semaphore(pdata->global_sem, GLOBLA_SEM_NAME);
	}
	else
	{
		philosopher_routine(created_philo);
		sem_close(pdata->global_sem);
		sem_close(fork_sem);
		exit(pdata->exit_status);
	}
}

int	main(int argc, char **argv)
{
	t_process	pdata;

	if (!init_args(argc, argv, &pdata.args))
		return (EXIT_FAILURE);
	unlink_semaphores();
	pdata.exit_status = -1;
	run_philosophers(&pdata);
	return (EXIT_SUCCESS);
}
