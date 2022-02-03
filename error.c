#include "philo.h"

int     error(char *str)
{
    int index;

    index = 0;
    printf("ERROR : %s\n", str);
    exit(1);
    return (1);
}
