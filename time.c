/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:24:16 by jmendes           #+#    #+#             */
/*   Updated: 2022/02/14 18:32:09 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	timer(struct timeval s_iniTime)
{
	int				time_ret;
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	time_ret = (s_time.tv_sec - s_iniTime.tv_sec) * 1000.0;
	time_ret += (s_time.tv_usec - s_iniTime.tv_usec) / 1000.0;
	return (time_ret);
}

int	time_to_die(struct timeval to_die, int time_die)
{
	int				ret;
	struct timeval	s_time;

	gettimeofday(&s_time, NULL);
	ret = (s_time.tv_sec - to_die.tv_sec) * 1000.0;
	ret += (s_time.tv_usec - to_die.tv_usec) / 1000.0;
	if (time_die > ret)
		return (0);
	else
		return (1);
}
