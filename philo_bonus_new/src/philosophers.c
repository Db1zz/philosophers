/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 14:23:27 by gonische          #+#    #+#             */
/*   Updated: 2024/10/31 16:29:02 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_philosopher(t_philosopher *philo, t_process *pdata)
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
