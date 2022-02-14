#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct  s_common
{
    pthread_mutex_t lock;
    int             dead;
}               t_common;

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
    pthread_mutex_t *forks;
    struct timeval  s_iniTime;
    struct timeval  to_die_t;
    struct timeval  action_time;
    t_common        *s_common;
}               t_arg;

//ARGS
void    arg_convert(t_arg *s_arg, int argc, char **argv);
void    arg_init(t_arg *s_arg);

//ACTION
void    *action(void *s_args);
void    printer(char *str, t_arg * s_arg);

//TIME
int     timer(struct timeval s_iniTime);
int     time_to_die(struct timeval to_die, int time_die);

//ERROR
int     error(char *str);

#endif