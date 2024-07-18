/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** ressource_gen
*/

#include "../include/zappy.h"

static const resource_s resource_time[] = {
    { 0.5 }, { 0.3 }, { 0.15 }, { 0.1 },
    { 0.1 }, { 0.08 }, { 0.5 }
};

void loop_gnr_rcs(server_t *server, int quantity, int which, int mode_filling)
{
    int x = rand() % server->config->width;
    int y = rand() % server->config->height;

    if (quantity <= 0)
        return;
    server->config->map[y][x]->objects[which] += 1;
    mode_filling ? send_map_mode_filling(x, y, server->config->map,
    server->clients) : 0;
    loop_gnr_rcs(server, --quantity, which, mode_filling);
}

void start_generate(server_t *server, map_s *count_map, int mode_filling)
{
    int calcul_size = server->config->width * server->config->height;

    for (int i = 0; i < 7; i++)
        loop_gnr_rcs(server, round(calcul_size * resource_time[i].density)
        - (mode_filling ? count_map->objects[i] : 0), i, mode_filling);
}

void check_and_spawn(server_t *server)
{
    map_s ***map = server->config->map;
    map_s count_map;
    int null_values[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    memcpy(count_map.objects, null_values, sizeof(null_values));
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[x]; x++) {
            count_map.objects[food] += map[y][x]->objects[food];
            count_map.objects[linemate] += map[y][x]->objects[linemate];
            count_map.objects[deraumere] += map[y][x]->objects[deraumere];
            count_map.objects[sibur] += map[y][x]->objects[sibur];
            count_map.objects[mendiane] += map[y][x]->objects[mendiane];
            count_map.objects[phiras] += map[y][x]->objects[phiras];
            count_map.objects[thystame] += map[y][x]->objects[thystame];
        }
    }
    start_generate(server, &count_map, 1);
}
