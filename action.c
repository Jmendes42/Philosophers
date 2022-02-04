#include "philo.h"

double  timer(struct timeval s_iniTime)
{
    struct timeval  s_time;
    int  time_ret;

    time_ret = 0;
    gettimeofday(&s_time, NULL);
    time_ret = s_time.tv_sec - s_iniTime.tv_sec;
    //time_ret = (s_time.tv_sec - s_iniTime.tv_sec) * 1000000 + (s_time.tv_usec - s_iniTime.tv_usec);
    return (time_ret);
}

void    printer(char *str, t_arg * s_arg)
{
    int time;

    pthread_mutex_lock(&s_arg->lock);
    time = timer(s_arg->s_iniTime);
    printf("%d %d %s\n", time, s_arg->index, str);
    pthread_mutex_unlock(&s_arg->lock);
}

void    eat(t_arg *s_arg)
{
    printer("eats", s_arg);
    sleep(s_arg->time_eat);
}

void    sleeping(t_arg *s_arg)
{
    printer("sleeps", s_arg);
    sleep(s_arg->time_sleep);
}

void    *action(void *s_args)
{
    t_arg   *s_arg;
    int     *forks;
    
    s_arg = (t_arg *)s_args;
    forks = malloc(sizeof(int) * s_arg->n_philos);
    while (s_arg->must_eat != 0)
    {
        if (s_arg->index > 0)
            pthread_mutex_lock(&s_arg->forks[s_arg->index - 1]);
        else
            pthread_mutex_lock(&s_arg->forks[s_arg->n_philos - 1]);
        pthread_mutex_lock(&s_arg->forks[s_arg->index]);
        printer("picks forks", s_arg);
        eat(s_arg);
        pthread_mutex_unlock(&s_arg->forks[s_arg->index]);
        if (s_arg->index > 0)
            pthread_mutex_unlock(&s_arg->forks[s_arg->index - 1]);
        else
            pthread_mutex_unlock(&s_arg->forks[s_arg->n_philos - 1]);
        sleeping(s_arg);
        printer("thinks", s_arg);
        s_arg->must_eat--;
    }
    return (0);
}