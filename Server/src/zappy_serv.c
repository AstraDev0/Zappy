/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** zappy_serv
*/

#include "../include/zappy.h"
server_t *server;

void handle_sigint(int sig __attribute__((unused)))
{
    clear(server);
    exit(0);
}

int zappy_server(server_t *init_server)
{
    server = init_server;
    init_map(server);
    init_socket(server, server->port);
    signal(SIGINT, handle_sigint);
    wait_client(server);
    printf("Waiting for connections on the port : %d\n", server->port);
    clock_gettime(4, &server->start);
    clock_gettime(4, &server->chrono_time_spawn_object);
    while (1) {
        child_sockets_wait_activity(server);
        handle_time(server);
        clients_connection(server, server->config);
        loop_check_disconnection(server);
    }
    return 0;
}
