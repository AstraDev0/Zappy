/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** main
*/

#include "include/zappy.h"

int main(int ac, char **av)
{
    server_t server = init_zappy_server();

    if (av[1] ? strcmp(av[1], "-help") == 0 ? 1 : 0 : 0)
        return usage();
    if (!check_args(ac, av, &server)) {
        free_team(server.config->team);
        free_config(&server);
        return 84;
    }
    return zappy_server(&server);
}
