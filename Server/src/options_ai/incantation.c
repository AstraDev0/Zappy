/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** incantation
*/

#include "../../include/zappy.h"

int check_ply_tl(clients_s *clients, clients_s *client, int nbr_plys)
{
    if (!clients)
        return nbr_plys == 0 ? 1 : 0;
    clients->mode > 0 && clients->level == client->level
    && clients->pst_player->X == client->pst_player->X
    && clients->pst_player->Y == client->pst_player->Y ? nbr_plys-- : 0;
    return check_ply_tl(clients->next, client, nbr_plys);
}

int check_tile_rsc(map_s *tile, map_s to_cpr)
{
    for (int i = 1; i < 7; i++)
        if (tile->objects[i] != to_cpr.objects[i])
            return 0;
    return 1;
}

int level_up_ict(clients_s *clients, clients_s *client, clients_s *all_clt)
{
    int length = 0;
    char *buffer;

    if (!clients)
        return 0;
    if (!(clients->mode > 0 && clients->level == client->level
    && clients->pst_player->X == client->pst_player->X
    && clients->pst_player->Y == client->pst_player->Y))
        return level_up_ict(clients->next, client, all_clt);
    client->level++;
    length = snprintf(NULL, 0, "Current level: %d",
    client->level) + 1;
    buffer = malloc(length * sizeof(char));
    snprintf(buffer, length, "Current level: %d",
    client->level);
    send_socket(client->control_fd, buffer);
    free(buffer);
    send_plv(NULL, all_clt, clients);
    return level_up_ict(clients->next, client, all_clt);
}

void send_tile_incantation(clients_s *clients, clients_s *client, char *msg)
{
    if (!clients)
        return;
    clients->mode > 0 && clients->level == client->level
    && clients->pst_player->X == client->pst_player->X
    && clients->pst_player->Y == client->pst_player->Y
    ? send_socket(clients->control_fd, msg) : 0;
    send_tile_incantation(clients->next, client, msg);
}

int check_incantation(server_t *server, clients_s *client)
{
    int x = client->pst_player->X;
    int y = client->pst_player->Y;
    map_s *map = server->config->map[y][x];
    if ((client->level == 1 && check_ply_tl(server->clients, client, 1)
    && check_tile_rsc(map,(map_s){0, 1, 0, 0, 0, 0, 0, 0, 0}))
    || (client->level == 2 && check_ply_tl(server->clients, client,
    2) && check_tile_rsc(map, (map_s){0, 1, 1, 1, 0, 0, 0, 0, 0}))
    || (client->level == 3 && check_ply_tl(server->clients, client, 2)
    && check_tile_rsc(map, (map_s){0, 2, 0, 1, 0, 2, 0, 0, 0}))
    || (client->level == 4 && check_ply_tl(server->clients, client, 4)
    && check_tile_rsc(map, (map_s){0, 1, 1, 2, 0, 1, 0, 0, 0}))
    || (client->level == 5 && check_ply_tl(server->clients, client, 4)
    && check_tile_rsc(map, (map_s){0, 1, 2, 1, 3, 0, 0, 0, 0}))
    || (client->level == 6 && check_ply_tl(server->clients, client, 6)
    && check_tile_rsc(map, (map_s){0, 1, 2, 3, 0, 1, 0, 0, 0}))
    || (client->level == 7 && check_ply_tl(server->clients, client, 6)
    && check_tile_rsc(map, (map_s){0, 2, 2, 2, 2, 2, 1, 0, 0})))
        return 1;
    return 0;
}
