#include "philo.h"

void    printer(char *str, int index)
{
    printf("%d is %s\n", index, str);
}

void    eat(t_arg *s_arg)
{
    printer("eating", s_arg->index);
    usleep(s_arg->time_eat);
}

void    *action(void *s_args)
{
    t_arg   *s_arg;

    s_arg = (t_arg *)s_args;
    printf("meals = %d\n", s_arg->must_eat);
    while (s_arg->must_eat != 0)
    {
        eat(s_arg);
        //sleeping(s_arg);
        s_arg->must_eat--;
    }
}