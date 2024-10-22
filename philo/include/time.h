/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:13:50 by gonische          #+#    #+#             */
/*   Updated: 2024/10/22 14:31:25 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <stdint.h>

typedef struct t_time
{
	uint64_t	time;
	uint64_t	pervious;
	uint64_t	diff;
}	t_time;

uint64_t	get_time(void);
void		init_time(t_time *time);
void		update_time(t_time *time);

#endif // TIME_H
