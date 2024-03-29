/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:23:52 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/28 12:16:39 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	arg_init(t_arg *s_arg)
{
	s_arg->control = 0;
	s_arg->forks = 0;
	s_arg->index = 0;
	s_arg->must_eat = -1;
	s_arg->n_philos = 0;
	s_arg->time_die = 0;
	s_arg->time_eat = 0;
	s_arg->time_sleep = 0;
	s_arg->time = 0;
	s_arg->s_common = malloc(sizeof(t_common));
	s_arg->s_common->dead = 0;
	gettimeofday(&s_arg->to_die_t, NULL);
	gettimeofday(&s_arg->action_time, NULL);
}

int	str_convert(char *str)
{
	int	index;
	int	result;

	index = 0;
	result = 0;
	while (str[index])
	{
		if (str[index] < 48 || str[index] > 57)
			error("Incorrect arguments");
		else
			result = result * 10 + (str[index] - '0');
		index++;
	}
	return (result);
}

void	arg_convert(t_arg *s_arg, int argc, char **argv)
{
	int	index;

	index = 1;
	while (index < argc)
	{
		if (index == 1)
			s_arg->n_philos = str_convert(argv[index]);
		if (index == 2)
			s_arg->time_die = str_convert(argv[index]);
		if (index == 3)
			s_arg->time_eat = str_convert(argv[index]);
		if (index == 4)
			s_arg->time_sleep = str_convert(argv[index]);
		if (index == 5)
			s_arg->must_eat = str_convert(argv[index]);
		index++;
	}
	s_arg->forks = malloc(sizeof(pthread_mutex_t) * s_arg->n_philos);
}
