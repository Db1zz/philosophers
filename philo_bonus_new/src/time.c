/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 23:20:18 by gonische          #+#    #+#             */
/*   Updated: 2024/10/31 14:19:37 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int64_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
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
	int64_t	time_curr;

	if (!time)
		return ;
	time_curr = get_time();
	time->diff = time_curr - time->pervious;
	time->time += time->diff;
	time->pervious = time_curr;
}

void	ft_sleep(int64_t ms)
{
	int64_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(100);
}
