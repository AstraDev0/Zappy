/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** usage
*/

#include "../include/zappy.h"

int usage(void)
{
    printf("USAGE: ./zappy_server -p port -x width \
-y height -n name1 name2 ... -c clientsNb -f freq\n");
    printf("\nport\tis the port number");
    printf("\nwidth\tis the width of the world");
    printf("\nheight\tis the height of the world");
    printf("\nnameX\tis the name of the team X");
    printf("\nclientsNb\tis the number of authorized clients per team");
    printf("\nfreq\tis the reciprocal of time unit for execution of actions");
    return 0;
}
