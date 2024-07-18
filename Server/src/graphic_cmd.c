/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** graphic_cmd
*/

#include "../include/zappy.h"

static const command_t COMMANDS[] = {
    { "msz", NULL, 0 },
    { "mct", NULL, 0 },{ "tna", NULL, 0 },
    { "bct", NULL, 0 }, { "ppo", NULL, 0 },
    { "plv", NULL, 0 }, { "pin", NULL, 0 },
    { "sgt", NULL, 0 }, { "sst", NULL, 0 } };

int check_order(char **cmd)
{
    for (int i = 0; i < 9; i++) {
        if (strcmp(cmd[0], COMMANDS[i].cmd) == 0)
            return i + 1;
    }
    return 0;
}

void parser_order_start(char **cmd, clients_s *client, server_t *server)
{
    int len = len_table(cmd);
    int order_valid = check_order(cmd);
    int number_one = len >= 2 ? check_number(cmd[1]) : 0;
    int number_two = len >= 3 ? check_number(cmd[2]) : 0;

    order_valid == 1 && len == 1 ? send_map_size(client, server, 1)
    : order_valid == 2 && len == 1 ? send_map(client, server)
    : order_valid == 3 && len == 1 ? send_team(client, server)
    : order_valid == 4 && len == 3 && check_limit_number(cmd,
    server->config->width, server->config->height) ? get_tile_map(cmd,
    client, server) : order_valid == 5 && len == 2 && number_one
    ? send_ppo(cmd, server->clients, client) : order_valid == 6 && len == 2
    && number_one ? send_plv(cmd, server->clients, client)
    : order_valid == 7 && len == 2 && number_one
    ? send_pin(cmd, server->clients, client) : order_valid == 8 && len == 1
    ? send_freq(client, server) : order_valid == 9 && len == 2 && number_one
    && atoi(cmd[1]) <= 10000 && atoi(cmd[1]) >= 2
    ? send_sst(cmd, client, server)
    : send_socket(client->control_fd, order_valid > 0 ? "sbp" : "suc");
}

void get_player(clients_s *client, server_t *server)
{
    if (!client)
        return;
    client->mode > 0 ? send_pnw(server->clients, client) : 0;
    get_player(client->next, server);
}

void send_enw(server_t *server, int i)
{
    int length = 0;
    char *result;
    team_t *team = server->config->team[i];
    eggs_t *eggs = team ? team->eggs : NULL;
    if (!team || !eggs)
        return;
    while (eggs) {
        length = snprintf(NULL, 0, "enw %d %d %d %d",
        eggs->id_egg, eggs->player_id,
        eggs->pst.X, eggs->pst.Y) + 1;
        result = malloc(length * sizeof(char));
        snprintf(result, length, "enw %d %d %d %d",
        eggs->id_egg, eggs->player_id,
        eggs->pst.X, eggs->pst.Y);
        send_socket_graphic_mode(server->clients, result);
        free(result);
        eggs = eggs->next;
    }
    send_enw(server, ++i);
}

void graphic_cmd(char **cmd, clients_s *client, server_t *server)
{
    if (client->mode == MODE_NOTHING) {
        client->mode = MODE_GRAPHIC;
        send_map_size(client, server, 1);
        send_freq(client, server);
        send_map(client, server);
        send_team(client, server);
        get_player(server->clients, server);
        send_enw(server, 0);
        return;
    }
    parser_order_start(cmd, client, server);
}
