/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:20:18 by gonische          #+#    #+#             */
/*   Updated: 2024/10/22 00:10:41 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

bool	thread_sleep_routine(uint64_t ms, bool (*f)(t_philosopher *), void *f_d)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
	{
		if (f != NULL && f(f_d))
			return (true);
	}
	return (false);
}

void	init_time(t_time *time)
{
	if (!time)
		return ;
	time->time = 0;
	time->pervious = get_time();
	time->diff = 0;
}

void	update_time(t_time *time)
{
	uint64_t	time_curr;

	if (!time)
		return ;
	time_curr = get_time();
	time->diff = time_curr - time->pervious;
	time->time += time->diff;
	time->pervious = time_curr;
}
