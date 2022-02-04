#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>



typedef struct  s_arg
{
    int n_philos;
    int time_die;
    int time_eat;
    int time_sleep;
    int must_eat;
    int index;
    int time;
    int control;
    pthread_mutex_t lock;
    pthread_mutex_t *forks;
    struct timeval s_iniTime;
}               t_arg;

void    arg_convert(t_arg *s_arg, int argc, char **argv);
void    arg_init(t_arg *s_arg);
void    *action(void *s_args);
//¡int     error(char *str);

#endif