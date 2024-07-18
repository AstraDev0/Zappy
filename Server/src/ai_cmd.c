/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** ai_cmd
*/

#include "../include/zappy.h"

static const command_t COMMANDS[] = { { "", error_cmd, 0 },
    { "Forward", forward, 7 }, { "Right", right, 7 }, { "Left", left, 7 },
    { "Look", look, 7 }, { "Inventory", inventory, 1 },
    { "Broadcast", broadcast, 7 }, { "Connect_nbr", connect_nbr, 0 },
    { "Fork", laying_agg, 0 }, { "Fork", fork_cmd_player, 42 },
    { "Eject", eject, 7 }, { "Take", take, 7 },
    { "Set", set, 7 }, { "Incantation", send_elvt_udw, 0 },
    { "Incantation", incantation, 300 } };

int add_order(server_t *server, command_t cmd, clients_s *client, char **cmd_a)
{
    client->list = add_queue(client->list, cmd, cmd_a);
    return 0;
}

void send_ebo(server_t *server, int count_eggs)
{
    int length = snprintf(NULL, 0, "ebo %d", count_eggs) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "ebo %d", count_eggs);
    send_socket_graphic_mode(server->clients, result);
    free(result);
}

pst_t *spawn_to_egg(clients_s *client, server_t *server)
{
    eggs_t *eggs = server->config->team[client->mode - 1]->eggs;
    int count_eggs = 0;
    int rdm = 0;
    for (; eggs && eggs->next; count_eggs++, eggs = eggs->next);
    eggs = server->config->team[client->mode - 1]->eggs;
    rdm = count_eggs <= 1 ? 0 : random_number(0, count_eggs - 1);
    for (count_eggs = 0; eggs && eggs->next; count_eggs++, eggs = eggs->next) {
        if (rdm == count_eggs)
            break;
    }
    client->pst_player = malloc(sizeof(pst_t));
    client->pst_player->O = eggs->pst.O;
    client->pst_player->Y = eggs->pst.Y;
    client->pst_player->X = eggs->pst.X;
    client->from_egg = 1;
    send_ebo(server, eggs->id_egg);
    server->config->team[client->mode - 1]->eggs
    = remove_egg(server->config->team[client->mode - 1]->eggs, eggs);
    return client->pst_player;
}

int init_ai(char **cmd, clients_s *client, server_t *server, int mode)
{
    if (place_client_team(server->clients, cmd[0], 0)
    >= server->config->team[mode - 1]->clientsNb)
        return error_cmd(server, client, cmd);
    client->mode = mode;
    client->pst_player = server->config->team[mode - 1]->eggs
    ? spawn_to_egg(client, server) : random_pst(server->config->height,
    server->config->width);
    server->config->map[client->pst_player->Y]
    [client->pst_player->X]->objects[player]++;
    client->team = server->config->nameX[mode - 1];
    send_pnw(server->clients, client);
    send_client_nb(client, server);
    send_map_size(client, server, 0);
    send_map_graphic(server->clients, server);
    clock_gettime(4, &client->start);
    return 0;
}

int ai_cmd(char **cmd, clients_s *client, server_t *server, int mode)
{
    int find = 0;

    if (client->mode == MODE_NOTHING)
        return init_ai(cmd, client, server, mode);
    for (int i = 0; i < 15; i++)
        if (strcmp(COMMANDS[i].cmd, cmd[0]) == 0)
            find = !add_order(server, COMMANDS[i], client, cmd);
    return !find ? add_order(server, COMMANDS[0], client, cmd) : 0;
}
