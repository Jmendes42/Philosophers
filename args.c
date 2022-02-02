#include "philo.h"

void   structs_create(t_arg s_args, t_arg *s_arg)
{
    s_arg->n_philos = s_args.n_philos;
    s_arg->time_die = s_args.time_die;
    s_arg->time_eat = s_args.time_eat;
    s_arg->time_sleep = s_args.time_sleep;
    s_arg->must_eat = s_args.must_eat;
    s_arg->index = s_args.index;
}


void    arg_init(t_arg *s_arg)
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
}

int     str_convert(char *str)
{
    int index;
    int result;

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

void    arg_convert(t_arg *s_arg, int argc, char **argv)
{
    int index;

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
}