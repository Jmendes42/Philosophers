#include "philo.h"

void    philo(t_arg s_args)
{
    int         index;
    t_arg       s_arg[s_args.n_philos - 1];
    pthread_t   philos[s_args.n_philos - 1];

    while (s_args.index < s_args.n_philos)
    {
        s_arg[s_args.index] = s_args;
        printf("Index = %d\n", s_arg[s_args.index].time_die);
        pthread_create(&philos[s_args.index], NULL, &action, (void *)&s_arg[s_args.index]);
        s_args.index++;
    }
    s_args.index = 0;
    while (s_args.index < s_args.n_philos)
    {
        printf("Index #2 = %d\n", s_args.index);
        pthread_join(philos[s_args.index], NULL);
        s_args.index++;
    }
}

int     main(int argc, char **argv)
{
    t_arg   s_args;

    if (argc < 5 || argc > 6)
            error("Wrong arguments number");
    arg_init(&s_args);
    arg_convert(&s_args, argc, argv);
    if (s_args.n_philos == 0)
        error("No philosofers");
    if (s_args.n_philos == 1)
    {
        usleep(s_args.time_die / 100);
        printf("%d 1 has died\n", s_args.time_die);
    }
    philo(s_args);
    return (0);
}