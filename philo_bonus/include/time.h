/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:13:50 by gonische          #+#    #+#             */
/*   Updated: 2024/10/22 15:01:32 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <stdint.h>

typedef struct t_time
{
	int64_t	time;
	int64_t	pervious;
	int64_t	diff;
}	t_time;

int64_t	get_time(void);
void	init_time(t_time *time);
void	update_time(t_time *time);

#endif // TIME_H
