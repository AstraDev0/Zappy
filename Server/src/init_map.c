/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** init_map
*/

#include "../include/zappy.h"

void loop_insert_height(map_s ***map, int height, int width, int y)
{
    if (y >= height)
        return;
    map[y] = malloc(sizeof(map_s *) * (width + 1));
    for (int x = 0; x < width; x++) {
        map[y][x] = malloc(sizeof(map_s));
        for (int i = 0; i < 9; i++)
            map[y][x]->objects[i] = 0;
    }
    map[y][width] = NULL;
    loop_insert_height(map, height, width, ++y);
}

void init_map(server_t *server)
{
    server->config->map = malloc(sizeof(map_s **) *
    (server->config->height + 1));
    loop_insert_height(server->config->map, server->config->height,
    server->config->width, 0);
    server->config->map[server->config->height] = 0;
    start_generate(server, NULL, 0);
}

void send_map_graphic(clients_s* clients, server_t *server)
{
    char* result = NULL;

    if (!clients)
        return;
    if (clients->mode != MODE_GRAPHIC)
        return send_map_graphic(clients->next, server);
    for (int y = 0; server->config->map[y]; y++) {
        for (int x = 0; server->config->map[y][x]; x++) {
            result = loop_parser_map(x, y, server->config->map);
            send_socket(clients->control_fd, result);
            free(result);
        }
    }
    send_map_graphic(clients->next, server);
}
