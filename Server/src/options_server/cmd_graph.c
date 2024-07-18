/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** cmd_graph
*/

#include "../../include/zappy.h"

void send_pgt_a_pdr(clients_s *client, server_t *server, int rsc_num, int mode)
{
    int length = snprintf(NULL, 0, mode ? "pdr %d %d" : "pgt %d %d",
    client->control_fd, rsc_num) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, mode ? "pdr %d %d" : "pgt %d %d"
    , client->control_fd, rsc_num);
    send_socket_graphic_mode(server->clients, result);
    free(result);
}

void send_pie(clients_s *client, clients_s *clients, int res)
{
    int length = snprintf(NULL, 0, "pie %d %d %d", client->pst_player->X,
    client->pst_player->Y, res) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "pie %d %d %d", client->pst_player->X,
    client->pst_player->Y, res);
    send_socket_graphic_mode(clients, result);
    free(result);
}

int end_game(clients_s *client, clients_s *clients)
{
    int length = snprintf(NULL, 0, "seg %d", client->control_fd) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length,  "seg %d", client->control_fd);
    send_socket_graphic_mode(clients, result);
    free(result);
}

void send_pic(server_t *server, clients_s *client)
{
    int length = snprintf(NULL, 0, "pic %d %d %d",
    client->pst_player->X, client->pst_player->Y, client->level) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "pic %d %d %d",
    client->pst_player->X, client->pst_player->Y, client->level);
    result = add_id_to_str(server->clients, result);
    send_socket_graphic_mode(server->clients, result);
    free(result);
}
