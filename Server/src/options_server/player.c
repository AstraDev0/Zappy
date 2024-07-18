/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** player
*/

#include "../../include/zappy.h"

void send_ppo(char **cmd, clients_s *clients, clients_s *client)
{
    clients_s *client_num = !cmd ? client
    : get_client_w_number(atoi(cmd[1]), clients);
    int length = snprintf(NULL, 0, "ppo %d %d %d %d",
    client_num->control_fd, client_num->pst_player->X,
    client_num->pst_player->Y, client_num->pst_player->O) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "ppo %d %d %d %d", client_num->control_fd,
    client_num->pst_player->X, client_num->pst_player->Y,
    client_num->pst_player->O);
    !cmd ? send_socket_graphic_mode(clients, result)
    : send_socket(client->control_fd, result);
    free(result);
}

void send_plv(char **cmd, clients_s *clients, clients_s *client)
{
    clients_s *client_num = !cmd ? client
    : get_client_w_number(atoi(cmd[1]), clients);
    int length = snprintf(NULL, 0, "plv %d %d",
    client_num->control_fd, client_num->level) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "plv %d %d",
    client_num->control_fd, client_num->level);
    !cmd ? send_socket_graphic_mode(clients ,result)
    : send_socket(client->control_fd, result);
    free(result);
}

void send_pin(char **cmd, clients_s *clients, clients_s *client)
{
    clients_s *client_num = !cmd ? client
    : get_client_w_number(atoi(cmd[1]), clients);
    map_s inventory = client_num->inventory;
    int length = snprintf(NULL, 0, "pin %d %d %d %d %d %d %d %d %d %d",
    client_num->control_fd, client_num->pst_player->X,
    client_num->pst_player->Y, inventory.objects[food],
    inventory.objects[linemate], inventory.objects[deraumere],
    inventory.objects[sibur], inventory.objects[mendiane],
    inventory.objects[phiras], inventory.objects[thystame]) + 1;
    char *result = malloc(length * sizeof(char));
    snprintf(result, length, "pin %d %d %d %d %d %d %d %d %d %d",
    client_num->control_fd, client_num->pst_player->X,
    client_num->pst_player->Y, inventory.objects[food],
    inventory.objects[linemate], inventory.objects[deraumere],
    inventory.objects[sibur], inventory.objects[mendiane],
    inventory.objects[phiras], inventory.objects[thystame]);
    !cmd ? send_socket_graphic_mode(clients ,result)
    : send_socket(client->control_fd, result);
    free(result);
}

void send_pnw(clients_s *clients, clients_s *client)
{
    int length = snprintf(NULL, 0, "pnw %d %d %d %d %d %s",
    client->control_fd, client->pst_player->X,
    client->pst_player->Y, client->pst_player->O,
    client->level, client->team) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "pnw %d %d %d %d %d %s", client->control_fd,
    client->pst_player->X, client->pst_player->Y, client->pst_player->O,
    client->level, client->team);
    send_socket_graphic_mode(clients, result);
    free(result);
}

void send_pdi(clients_s *clients, clients_s *client)
{
    int length = snprintf(NULL, 0, "pdi %d",
    client->control_fd) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "pdi %d",
    client->control_fd);
    send_socket_graphic_mode(clients, result);
    free(result);
}
