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

    time = timer(s_arg->s_iniTime);
    printf("%d %d %s\n", time, s_arg->index, str);
}

void    eat(t_arg *s_arg)
{
    //pthread_mutex_lock(&lock);
    printer("eats", s_arg);
    sleep(s_arg->time_eat);
    //pthread_mutex_unlock(&lock);
}

void    sleeping(t_arg *s_arg)
{
    printer("sleeps", s_arg);
    sleep(s_arg->time_sleep);
}

void    think(t_arg *s_arg)
{
    printer("thinks", s_arg);
}

void    *action(void *s_args)
{

    t_arg   *s_arg;

    s_arg = (t_arg *)s_args;
    while (s_arg->must_eat != 0)
    {
        //printf("index == %d\n", s_arg->index);
        eat(s_arg);
        sleeping(s_arg);
        think(s_arg);
        pthread_mutex_lock(&lock);
        printer("picks fork", s_arg);
        s_arg->forks++;
        pthread_mutex_unlock(&lock);
        if (s_arg->control == 0)
        {
            s_arg->time = timer(s_arg->s_iniTime);
            if (s_arg->time < s_arg->time_eat * s_arg->n_philos)
                sleep(s_arg->time_eat * s_arg->n_philos - s_arg->time);
            s_arg->control++;
        }
        s_arg->must_eat--;
    }
}