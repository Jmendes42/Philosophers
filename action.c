#include "philo.h"

void    printer(char *str, t_arg * s_arg)
{
    int time;
    pthread_mutex_t lock;

    pthread_mutex_lock(&s_arg->s_common->lock);
    time = timer(s_arg->s_iniTime);
    printf("%d %d %s\n", time, s_arg->index, str);
    pthread_mutex_unlock(&s_arg->s_common->lock);
}

int     to_die(t_arg *s_arg)
{
    if (s_arg->s_common->dead == 0)
    {
        pthread_mutex_lock(&s_arg->s_common->lock);
        s_arg->s_common->dead = time_to_die(s_arg->to_die, s_arg->time_die);
        pthread_mutex_unlock(&s_arg->s_common->lock);
        if (s_arg->s_common->dead == 1)
        {
            printer("died", s_arg);
            return (1);
        }
        else if (s_arg->s_common->dead == 0)
        {
            return (0);
        }
    }
    else
        return (1);
}



int    eat(t_arg *s_arg)
{
    if (s_arg->index > 0)
        pthread_mutex_lock(&s_arg->forks[s_arg->index - 1]);
    else
        pthread_mutex_lock(&s_arg->forks[s_arg->n_philos - 1]);
    pthread_mutex_lock(&s_arg->forks[s_arg->index]);
    if (to_die(s_arg) == 1)
            return (1);
    printer("picks forks", s_arg);
    printer("eats", s_arg);
    gettimeofday(&s_arg->to_die, NULL);
    usleep(s_arg->time_eat * 1000);
    pthread_mutex_unlock(&s_arg->forks[s_arg->index]);
    if (s_arg->index > 0)
        pthread_mutex_unlock(&s_arg->forks[s_arg->index - 1]);
    else
        pthread_mutex_unlock(&s_arg->forks[s_arg->n_philos - 1]);
    if (to_die(s_arg) == 1)
            return (1);
    return (0);
}

int    sleeping(t_arg *s_arg)
{
    if (to_die(s_arg) == 1)
            return (1);
    printer("sleeps", s_arg);
    usleep(s_arg->time_sleep * 1000);
    if (to_die(s_arg) == 1)
            return (1);
    return (0);
}

int    thinking(t_arg *s_arg)
{
    if (to_die(s_arg) == 1)
            return (1);
    printer("thinks", s_arg);
    if (to_die(s_arg) == 1)
            return (1);
    return (0);
}


void    *action(void *s_args)
{
    t_arg   *s_arg;
    
    s_arg = (t_arg *)s_args;
    while (s_arg->must_eat != 0)
    {
        if (eat(s_arg) == 1)
            return (0);
        if (to_die(s_arg) == 1)
            return (0);
        if (sleeping(s_arg) == 1)
            return (0);
        if (thinking(s_arg) == 1)
            return (0);
        s_arg->must_eat--;
    }
    return (0);
}