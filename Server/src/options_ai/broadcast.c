/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** broadcast
*/

#include "../../include/zappy.h"

int send_pbc(clients_s *client, clients_s *clients, char *msg)
{
    int length = snprintf(NULL, 0, "pbc %d %s", client->control_fd, msg) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length,  "pbc %d %s", client->control_fd, msg);
    send_socket_graphic_mode(clients, result);
    free(result);
}

int source_broatcast_clc(pst_t *src, pst_t *target)
{
    int x_distance = src->X - target->X;
    int y_distance = src->Y - target->Y;
    int direction = x_distance == 0 && y_distance > 0
    ? target->O == 2 ? 3 : target->O == 3 ? 5 : target->O == 4 ? 7 : 1
    : x_distance == 0 && y_distance < 0 ? target->O == 2
    ? 7 : target->O == 3 ? 1 : target->O == 4 ? 3 : 5 : x_distance < 0
    && y_distance == 0 ? target->O == 2 ? 5 : target->O == 3 ? 7
    : target->O == 4 ? 1 : 3 : x_distance < 0 && y_distance == 0
    ? target->O == 2 ? 1 : target->O == 3 ? 3
    : target->O == 4 ? 5 : 7 : x_distance < 0 && y_distance < 0
    ? target->O == 2 ? 6 : target->O == 3 ? 8 : target->O == 4 ? 2 : 4 :
    x_distance > 0 && y_distance < 0 ? target->O == 2 ? 8
    : target->O == 3 ? 2 : target->O == 3 ? 4 : 6
    : x_distance > 0 && y_distance > 0 ? target->O == 2 ? 2
    : target->O == 3 ? 4 : target->O == 4 ? 6 : 8
    : x_distance < 0 && y_distance > 0 ? target->O == 2 ? 4
    : target->O == 3 ? 6 : target->O == 4 ? 8 : 2 : 0;

    return direction;
}

void send_broadcast(clients_s *clients, clients_s *client, char *msg)
{
    int length = 0;
    char *result;
    int direction = 0;

    if (!clients)
        return;
    if (clients == client || clients->mode == MODE_GRAPHIC)
        return send_broadcast(clients->next, client, msg);
    direction = source_broatcast_clc(client->pst_player, clients->pst_player);
    length = snprintf(NULL, 0, "message %d, %s", direction, msg) + 1;
    result = malloc(length * sizeof(char));

    snprintf(result, length,  "message %d, %s", direction, msg);
    send_socket(clients->control_fd, result);
    free(result);
    return send_broadcast(clients->next, client, msg);
}

int broadcast(server_t *server, clients_s *client, char **cmd)
{
    clients_s *clients = server->clients;
    char *buffer = NULL;

    if (!cmd[1])
        return send_socket(client->control_fd, "ko");
    for (int i = 1; cmd[i]; i++) {
        buffer = buffer ? add_value_to_str(buffer, " ") : buffer;
        buffer = add_value_to_str(buffer, cmd[i]);
    }
    send_broadcast(server->clients, client, buffer);
    send_pbc(client, server->clients, buffer);
    free(buffer);
    return send_socket(client->control_fd, "ok");
}
