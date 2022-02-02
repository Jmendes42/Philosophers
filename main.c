#include "philo.h"

// double  timer(struct timeval s_iniTime)
// {
//     struct timeval  s_time;
//     int  time_ret;

//     time_ret = 0;
//     gettimeofday(&s_time, NULL);
//     time_ret = (s_time.tv_sec - s_iniTime.tv_sec) * 1000000 + (s_time.tv_usec - s_iniTime.tv_usec);
//     return (time_ret);
// }

void    philo(t_arg s_args)
{
    int         index;
    int         forks[s_args.n_philos];
    t_arg       s_arg[s_args.n_philos];
    pthread_t   philos[s_args.n_philos - 1];

    gettimeofday(&s_args.s_iniTime, NULL);
    pthread_mutex_init(&lock, NULL);
    memset(forks, 0, s_args.n_philos);
    printf("%d\n", forks[2]);
    while (s_args.index < s_args.n_philos)
    {
        s_arg[s_args.index] = s_args;
        //printf("index == %d\n", s_arg[s_args.index].index);
        pthread_create(&philos[s_args.index], NULL, &action, (void *)&s_arg[s_args.index]);
        sleep(s_arg->time_eat);
        s_args.index++;
    }
    s_args.index = 0;
    while (s_args.index < s_args.n_philos)
    {
        pthread_join(philos[s_args.index], NULL);
        s_args.index++;
    }
        pthread_mutex_destroy(&lock);
}

int     main(int argc, char **argv)
{
    t_arg   s_args;

    // int argc = 5;
    // char **argv;

    // argv = malloc(sizeof(char *) * 5);
    // for (int i = 0; i < 5; i++)
    //     argv[i] = malloc(3);

    // argv[1] = "2";
    // argv[2] = "100";
    // argv[3] = "800";
    // argv[4] = "800";
    
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
    }
    philo(s_args);
    return (0);
}