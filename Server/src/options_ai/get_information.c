/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** get_information
*/

#include "../../include/zappy.h"

int look(server_t *server, clients_s *client, char **cmd)
{
    char *result;

    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    result = process_look(0, client->pst_player, server->config,
    client->level);
    send_socket(client->control_fd, result);
    free(result);
    return 0;
}

int inventory(server_t *server, clients_s *client, char **cmd)
{
    int length = 0;
    char *result;
    map_s ivtr = client->inventory;

    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    length = snprintf(NULL, 0, "[ food %d, linemate %d, deraumere %d, \
sibur %d, mendiane %d, phiras %d, thystame %d ]", ivtr.objects[food],
    ivtr.objects[linemate], ivtr.objects[deraumere], ivtr.objects[sibur],
    ivtr.objects[mendiane], ivtr.objects[phiras], ivtr.objects[thystame]) + 1;
    result = malloc(length * sizeof(char));
    snprintf(result, length, "[ food %d, linemate %d, deraumere %d, \
sibur %d, mendiane %d, phiras %d, thystame %d ]", ivtr.objects[food],
    ivtr.objects[linemate], ivtr.objects[deraumere], ivtr.objects[sibur],
    ivtr.objects[mendiane], ivtr.objects[phiras], ivtr.objects[thystame]);
    send_socket(client->control_fd, result);
    free(result);
    return 0;
}

int connect_nbr(server_t *server, clients_s *client, char **cmd)
{
    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    send_client_nb(client, server);
    return 0;
}
