/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** init_function
*/

#include "../include/zappy.h"

void init_socket(server_t *server, int port)
{
    if ((server->control_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_server("server failed", server->control_fd);
    if (setsockopt(server->control_fd, SOL_SOCKET, SO_REUSEADDR
    | 15, &server->opt, sizeof(server->opt)))
        error_server("setsockopt", server->control_fd);
    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);
    if (bind(server->control_fd, (struct sockaddr*)&server->address,
    sizeof(server->address)) < 0)
        error_server("bind failed", server->control_fd);
}

server_t init_zappy_server_next(server_t server, opt_t *config)
{
    uint64_t ms;

    server.config = config;
    server.port = 4242;
    server.opt = 1;
    server.clients = NULL;
    server.addrlen = sizeof(server.address);
    server.time_before_object_spawn = TIME_BEFORE_OBJECT_SPAWN;
    server.timeval.tv_sec = 0;
    ms = 1000000 / server.config->freq;
    server.timeval.tv_usec = ms;
    server.current_timeval.tv_sec = 0;
    server.current_timeval.tv_usec = ms;
    return server;
}

server_t init_zappy_server(void)
{
    server_t server;
    opt_t *config = malloc(sizeof(opt_t));

    config->team = malloc(sizeof(team_t *) * 3);
    for (int i = 0; i < 2; i++) {
        config->team[i] = malloc(sizeof(team_t));
        config->team[i]->clientsNb = 3;
        config->team[i]->eggs = NULL;
    }
    config->id_eggs_ctn = 0;
    config->team[2] = NULL;
    config->freq = 100;
    config->height = 10;
    config->width = 10;
    config->nameX = malloc(sizeof(char *) * 3);
    config->nameX[0] = "Team1";
    config->nameX[1] = "Team2";
    config->nameX[2] = NULL;
    return init_zappy_server_next(server, config);
}
