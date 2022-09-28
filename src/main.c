/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:24:10 by jmendes           #+#    #+#             */
/*   Updated: 2022/09/28 12:16:48 by jmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	printer(char *str, t_arg *s_arg)
{
	int				time;
	pthread_mutex_t	lock;
	int static		control;

	if (!control)
		control = 0;
	pthread_mutex_lock(&s_arg->s_common->lock);
	time = timer(s_arg->s_init_time);
	if (s_arg->s_common->dead == 1 && control == 0)
	{
		printf("%d %d %s\n", time, s_arg->index, str);
		control++;
	}
	if (s_arg->s_common->dead == 0)
		printf("%d %d %s\n", time, s_arg->index, str);
	pthread_mutex_unlock(&s_arg->s_common->lock);
}

void	philo(t_arg s_args)
{
	int			index;
	t_arg		s_arg[200];
	pthread_t	philos[200];

	index = -1;
	gettimeofday(&s_args.s_init_time, NULL);
	while (++index < s_args.n_philos)
		pthread_mutex_init(&s_args.forks[index], NULL);
	pthread_mutex_init(&s_args.s_common->lock, NULL);
	while (s_args.index < s_args.n_philos)
	{
		s_arg[s_args.index] = s_args;
		pthread_create(&philos[s_args.index], NULL, &action,
			(void *)&s_arg[s_args.index]);
		s_args.index++;
	}
	s_args.index = -1;
	while (++s_args.index < s_args.n_philos)
		pthread_join(philos[s_args.index], NULL);
	index = -1;
	while (++index < s_args.n_philos)
		pthread_mutex_destroy(&s_args.forks[index]);
	pthread_mutex_destroy(&s_args.s_common->lock);
}

int	edge_cases(int argc, t_arg s_args)
{
	if (argc < 5 || argc > 6)
	{
		error("Wrong arguments number");
		return (1);
	}
	if (s_args.n_philos == 0)
	{
		error("No philosofers");
		return (1);
	}
	if (s_args.n_philos == 1)
	{
		usleep(s_args.time_die * 1000);
		printf("%d 0 has died\n", s_args.time_die);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_arg	s_args;

	arg_init(&s_args);
	arg_convert(&s_args, argc, argv);
	if (edge_cases(argc, s_args) == 1)
		return (0);
	philo(s_args);
	free (s_args.s_common);
	return (0);
}
