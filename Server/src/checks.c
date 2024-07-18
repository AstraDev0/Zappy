/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** checker
*/

#include "../include/zappy.h"

void n_option(server_t *server, char **av)
{
    int cursor = 0;
    int interval = 0;
    int j = 0;
    char **res = NULL;

    for (; av[cursor] && strcmp(av[cursor], "-n") != 0; cursor++);
    for (cursor++; av[cursor] && av[cursor][0] != '-'; cursor++, interval++);
    res = malloc(sizeof(char *) * (interval + 1));
    for (int i = cursor - interval; i < cursor; i++, j++)
        res[j] = av[i];
    res[interval] = NULL;
    free(server->config->nameX);
    server->config->nameX = res;
}

void insert_clt_nbr(server_t *server, int nbr)
{
    int len = len_table(server->config->nameX);

    free_team(server->config->team);
    server->config->team = malloc(sizeof(team_t *) * (len + 1));
    for (int i = 0; i < len; i++) {
        server->config->team[i] = malloc(sizeof(team_t));
        server->config->team[i]->clientsNb = nbr;
        server->config->team[i]->eggs = NULL;
    }
    server->config->team[len] = NULL;
}

int check_option(int opt, server_t *server, char **av)
{
    if (!error_arguments(av, opt))
        return 0;
    switch (opt) {
        case ('p'): server->port = atoi(optarg) == 0 ?
        random_port() : atoi(optarg); break;
        case ('x'): server->config->width = atoi(optarg); break;
        case ('y'): server->config->height = atoi(optarg); break;
        case ('n'): n_option(server, av); break;
        case ('c'): insert_clt_nbr(server, atoi(optarg)); break;
        case ('f'): server->config->freq = atoi(optarg); break;
    }
    return 1;
}

int check_args(int ac, char **av, server_t *server)
{
    int opt = 0;

    srand(time(NULL));
    while (ac > 1 && (opt = getopt(ac, av, "p:x:y:n:c:f:")) != -1) {
        if (opt == '?' || !check_option(opt, server, av))
            return 0;
    }
    return 1;
}
