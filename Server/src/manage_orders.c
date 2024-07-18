/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** handle_order
*/

#include "../include/zappy.h"

void get_order(char *order, clients_s *client, server_t *server)
{
    char **cmd = my_split(order, " ");

    client->mode == MODE_NOTHING ? strcmp(order, "GRAPHIC") == 0 ?
    graphic_cmd(cmd, client, server) :
    match_table(order, server->config->nameX, 0) > 0 ?
    ai_cmd(cmd, client, server,
    match_table(order, server->config->nameX, 0)) :
    send_socket(client->control_fd, "ko") : client->mode == MODE_GRAPHIC ?
    graphic_cmd(cmd, client, server) : client->mode > 0 ?
    ai_cmd(cmd, client, server, 0) : 0;
    table_free(cmd);
}

int send_socket(int sd, char *msg)
{
    char *buffer;

    if (MAXDATASIZE < strlen(msg)) {
        fprintf(stderr, "message size too large");
        return 84;
    }
    if ((buffer = malloc(strlen(msg) + 2)) == 0)
        return 84;
    if (sprintf(buffer, "%s\n", msg) <= 0 ||
    write(sd, buffer, strlen(buffer)) < 0)
        perror("error writing to socket");
    free(buffer);
    return 0;
}

int send_socket_graphic_mode(clients_s* clients, char *result)
{
    if (!clients)
        return 0;
    clients->mode == MODE_GRAPHIC ?
    send_socket(clients->control_fd, result) : 0;
    return send_socket_graphic_mode(clients->next, result);
}
