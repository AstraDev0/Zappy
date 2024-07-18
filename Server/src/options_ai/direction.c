/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** direction
*/

#include "../../include/zappy.h"

int forward(server_t *server, clients_s *client, char **cmd)
{
    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    server->config->map[client->pst_player->Y]
    [client->pst_player->X]->objects[player]--;
    client->pst_player->O == 3 ?
    client->pst_player->Y = client->pst_player->Y == 0 ?
    server->config->height - 1 : client->pst_player->Y - 1
    : client->pst_player->O == 2 ?
    client->pst_player->X = client->pst_player->X
    >= server->config->width - 1 ? 0 : client->pst_player->X + 1
    : client->pst_player->O == 1 ? client->pst_player->Y
    = client->pst_player->Y >= server->config->height - 1 ? 0
    : client->pst_player->Y + 1 : client->pst_player->O == 4
    ? client->pst_player->X = client->pst_player->X == 0
    ? server->config->width - 1 : client->pst_player->X - 1 : 0;
    server->config->map[client->pst_player->Y]
    [client->pst_player->X]->objects[player]++;
    send_ppo(NULL, server->clients, client);
    return send_socket(client->control_fd, "ok");
}

int right(server_t *server, clients_s *client, char **cmd)
{
    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    client->pst_player->O += 1;
    client->pst_player->O > 4 ? client->pst_player->O = 1 : 0;
    send_ppo(NULL, server->clients, client);
    return send_socket(client->control_fd, "ok");
}

int left(server_t *server, clients_s *client, char **cmd)
{
    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    client->pst_player->O -= 1;
    client->pst_player->O < 1 ? client->pst_player->O = 4 : 0;
    send_ppo(NULL, server->clients, client);
    return send_socket(client->control_fd, "ok");
}
