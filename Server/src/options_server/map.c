/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** map
*/

#include "../../include/zappy.h"

char *loop_parser_map(int x, int y, map_s ***map)
{
    int length = 0;
    char *result;
    map_s *map_x_y = map[y][x];

    length = snprintf(NULL, 0, "bct %d %d %d %d %d %d %d %d %d",
    x, y, map_x_y->objects[food], map_x_y->objects[linemate],
    map_x_y->objects[deraumere],
    map_x_y->objects[sibur], map_x_y->objects[mendiane],
    map_x_y->objects[phiras], map_x_y->objects[thystame]) + 1;
    result = malloc(length * sizeof(char));
    snprintf(result, length, "bct %d %d %d %d %d %d %d %d %d",
    x, y, map_x_y->objects[food],
    map_x_y->objects[linemate], map_x_y->objects[deraumere],
    map_x_y->objects[sibur], map_x_y->objects[mendiane],
    map_x_y->objects[phiras], map_x_y->objects[thystame]);
    return result;
}

void send_map_mode_filling(int x, int y, map_s ***map, clients_s* clients)
{
    int length = 0;
    char *result = NULL;
    map_s *map_x_y = map[y][x];

    result = loop_parser_map(x, y, map);
    send_socket_graphic_mode(clients, result);
    free(result);
}

void send_map(clients_s* client, server_t *server)
{
    char* result = NULL;

    for (int y = 0; server->config->map[y]; y++) {
        for (int x = 0; server->config->map[y][x]; x++) {
            result = loop_parser_map(x, y, server->config->map);
            send_socket(client->control_fd, result);
            free(result);
        }
    }
}

void send_map_size(clients_s *client, server_t *server, int msz)
{
    int length = snprintf(NULL, 0, msz ?
    "msz %d %d" : "%d %d", server->config->width, server->config->height) + 1;
    char* result = malloc(length * sizeof(char));

    snprintf(result, length, msz ?
    "msz %d %d" : "%d %d", server->config->width, server->config->height);
    send_socket(client->control_fd, result);
    free(result);
}

void get_tile_map(char **cmd, clients_s *client, server_t *server)
{
    int x = atoi(cmd[1]);
    int y = atoi(cmd[2]);
    char *result = NULL;
    int length = 0;
    map_s *map = server->config->map[y][x];

    result = loop_parser_map(x, y, server->config->map);
    send_socket(client->control_fd, result);
    free(result);
}
