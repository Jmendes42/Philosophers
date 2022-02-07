#include "philo.h"

void    printer(char *str, t_arg * s_arg)
{
    int time;
    pthread_mutex_t lock;

    pthread_mutex_lock(&s_arg->lock);
    time = timer(s_arg->s_iniTime);
    printf("%d %d %s\n", time, s_arg->index, str);
    pthread_mutex_unlock(&s_arg->lock);
}

void    eat(t_arg *s_arg)
{
    printer("eats", s_arg);
    gettimeofday(&s_arg->to_die, NULL);
    usleep(s_arg->time_eat * 1000);
}

void    sleeping(t_arg *s_arg)
{

    printer("sleeps", s_arg);
    usleep(s_arg->time_sleep * 1000);
}

int     to_die(t_arg *s_arg, int *dead)
{
    if (*dead == 0)
    {
        *dead = time_to_die(s_arg->to_die, s_arg->time_die);
        if (*dead == 1)
        {
            printer("died", s_arg);
            return (1);
        }
        else if (*dead == 0)
        {
            printf("%d Chegou aqui e escrevi uma frase desnecessariamente longa para distinguir do resto das frases\n", *dead);
            return (0);
        }
    }
    else
        return (1);
}

void    *action(void *s_args)
{
    int     dead;
    t_arg   *s_arg;
    pthread_mutex_t lock;
    
    dead = 0;
    s_arg = (t_arg *)s_args;
    pthread_mutex_init(&lock, NULL);
    while (s_arg->must_eat != 0)
    {
        pthread_mutex_lock(&lock);
        dead = time_to_die(s_arg->to_die, s_arg->time_die);
        if (to_die(s_arg, &dead) == 1)
            return(0);
        pthread_mutex_unlock(&lock);
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
    pthread_mutex_destroy(&lock);
    return (0);
}