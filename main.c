#include "philo.h"

void    philo(t_arg s_args)
{
    int         index;
    t_arg       s_arg[s_args.n_philos];
    pthread_t   philos[s_args.n_philos];

    index = 0;
    gettimeofday(&s_args.s_iniTime, NULL);
    while (index < s_args.n_philos)
    {
        pthread_mutex_init(&s_args.forks[index], NULL);
        index++;
    }
    pthread_mutex_init(&s_args.s_common->lock, NULL);
    while (s_args.index < s_args.n_philos)
    {
        s_arg[s_args.index] = s_args;
        pthread_create(&philos[s_args.index], NULL, &action, (void *)&s_arg[s_args.index]);
        s_args.index++;
    }
    s_args.index = 0;
    while (s_args.index < s_args.n_philos)
    {
        pthread_join(philos[s_args.index], NULL);
        s_args.index++;
    }
    index = 0;
    while (index > s_args.n_philos)
    {
        pthread_mutex_destroy(&s_args.forks[index]);
        index++;
    }
    pthread_mutex_destroy(&s_args.s_common->lock);

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
        usleep(s_args.time_die * 1000);
        printf("%d 0 has died\n", s_args.time_die);
        return (0);
    }
    philo(s_args);
    free (s_args.s_common);
    return (0);
}