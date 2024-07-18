/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** get_client_info
*/

#include "../include/zappy.h"

clients_s *get_client_w_number(int num, clients_s *clients)
{
    if (!clients)
        return NULL;
    if (clients->control_fd == num)
        return clients;
    get_client_w_number(num, clients->next);
}

int place_client_team(clients_s *clients, char *team, int i)
{
    if (!clients)
        return i;
    if (clients->mode > 0 && strcmp(clients->team, team) == 0)
        return place_client_team(clients->next, team, ++i);
    return place_client_team(clients->next, team, i);
}
