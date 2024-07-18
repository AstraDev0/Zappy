/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** action
*/

#include "../../include/zappy.h"

static const command_t resource[] = {
    { "food", NULL, 0 }, { "linemate", NULL, 0 }, { "deraumere", NULL, 0 },
    { "sibur", NULL, 0 }, { "mendiane", NULL, 0 },
    { "phiras", NULL, 0 }, { "thystame", NULL, 0 }
    };


int take(server_t *server, clients_s *client, char **cmd)
{
    int object = -1;
    int y = client->pst_player->Y;
    int x = client->pst_player->X;
    if (!cmd[1] || len_table(cmd) > 2)
        return send_socket(client->control_fd, "ko");
    for (int i = 0; i < 7; i++) {
        if (strcmp(cmd[1], resource[i].cmd) == 0) {
            object = i;
            break;
        }
    }
    if (object == -1 || server->config->map[y][x]->objects[object] == 0)
        return send_socket(client->control_fd, "ko");
    server->config->map[y][x]->objects[object]--;
    client->inventory.objects[object]++;
    send_pgt_a_pdr(client, server, object, 0);
    send_pin(NULL, server->clients, client);
    free(loop_parser_map(x, y, server->config->map));
    return send_socket(client->control_fd, "ok");
}

int set(server_t *server, clients_s *client, char **cmd)
{
    int object = -1;
    int y = client->pst_player->Y;
    int x = client->pst_player->X;
    if (!cmd[1] || len_table(cmd) > 2)
        return send_socket(client->control_fd, "ko");
    for (int i = 0; i < 7; i++) {
        if (strcmp(cmd[1], resource[i].cmd) == 0) {
            object = i;
            break;
        }
    }
    if (object == -1 || client->inventory.objects[object] == 0)
        return send_socket(client->control_fd, "ko");
    server->config->map[y][x]->objects[object]++;
    client->inventory.objects[object]--;
    send_pgt_a_pdr(client, server, object, 1);
    send_pin(NULL, server->clients, client);
    free(loop_parser_map(x, y, server->config->map));
    return send_socket(client->control_fd, "ok");
}

int send_elvt_udw(server_t *server, clients_s *client, char **cmd)
{
    check_incantation(server, client) ?
    send_tile_incantation(server->clients, client, "Elevation underway")
    : send_socket(client->control_fd, "ko");
    send_pic(server, client);
}

int incantation(server_t *server, clients_s *client, char **cmd)
{
    int res = check_incantation(server, client);

    send_pie(client, server->clients, res);
    res ? level_up_ict(server->clients, client, server->clients)
    : send_socket(client->control_fd, "ko");
    client->level == 8 ? end_game(client, server->clients) : 0;
    return 0;
}
