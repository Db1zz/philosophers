/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:20:18 by gonische          #+#    #+#             */
/*   Updated: 2024/10/21 17:56:13 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

uint64_t	get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void	update_time(t_time *time)
{
	time->tdiff = get_time() - time->tlast;
	time->timestamp += time->tdiff;
	time->tstate += time->tdiff;
	time->tsince_last_meal += time->tdiff;
	time->tlast += time->tdiff;
}

void	init_time(t_time *time)
{
	time->timestamp = 0;
	time->tstate = 0;
	time->tsince_last_meal = 0;
	time->tlast = get_time();
}

// sps Fedya za etu function
void	thread_sleep(uint64_t ms)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) <= ms);
}
