/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** eject
*/

#include "../../include/zappy.h"

void send_pex(server_t *server, clients_s *client)
{
    int length = snprintf(NULL, 0, "pex %d", client->control_fd) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "pex %d", client->control_fd);
    send_socket_graphic_mode(server->clients, result);
    free(result);
}

int area_direction_clc(int o_source, int o_target)
{
    return (o_source == 1 ? (o_target == 1 ? 1 : o_target == 2
    ? 7 : o_target == 3 ? 5 : o_target == 4 ? 3 : 0) : o_source == 2 ?
    (o_target == 1 ? 3 : o_target == 2 ? 1 : o_target == 3
    ? 7 : o_target == 4 ? 5 : 0) : o_source == 3 ? (o_target == 1 ? 5
    : o_target == 2 ? 3 : o_target == 3 ? 1 : o_target == 4 ? 7 : 0) :
    o_source == 4 ? (o_target == 1 ? 7 : o_target == 2 ? 5 : o_target == 3
    ? 3 : o_target == 4 ? 1 : 0) : 0);
}

void send_eject(clients_s *clients, clients_s *client)
{
    int direction = area_direction_clc(client->pst_player->O,
    clients->pst_player->O);

    int length = snprintf(NULL, 0, "eject: %d", direction) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "eject: %d", direction);
    send_socket(clients->control_fd, result);
    free(result);
}

int loop_ejct(server_t *server, clients_s *clients, clients_s *client, int res)
{
    if (!clients)
        return res;
    if (clients == client || !(clients->mode > 0
    && clients->pst_player->X == client->pst_player->X
    && clients->pst_player->Y == client->pst_player->Y))
        return loop_ejct(server, clients->next, client, res);
    res = 1;
    send_pex(server, client);
    forward(server, clients, (char *[]){"NULL", NULL});
    send_eject(clients, client);
    return loop_ejct(server, clients->next, client, res);
}

int eject(server_t *server, clients_s *client, char **cmd)
{
    int res = loop_ejct(server, server->clients, client, 0);

    res = loop_eject_eggs(server, client, 0, 0) ? 1 : res;
    send_socket(client->control_fd, res ? "ok" : "ko");
}
