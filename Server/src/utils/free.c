/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** free
*/

#include "../../include/zappy.h"

void table_free(char **table)
{
    for (int i = 0; table[i]; i++)
        free(table[i]);
    free(table);
}

void map_free(map_s ***map)
{
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x]; x++)
            free(map[y][x]);
        free(map[y]);
    }
    free(map);
}

void free_config(server_t *server)
{
    free(server->config->nameX);
    free(server->config);
}

void free_client_detail(clients_s *client)
{
    remove_queues(client->list);
    free(client->pst_player);
    free(client);
}

void free_team(team_t **teams)
{
    for (int i = 0; teams[i]; i++) {
        remove_eggs(teams[i]->eggs);
        free(teams[i]);
    }
    free(teams);
}
