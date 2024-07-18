/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** args
*/

#include "../../include/zappy.h"

void send_client_nb(clients_s *client, server_t *server)
{
    int number = server->config->team[client->mode - 1]->clientsNb
    - place_client_team(server->clients, client->team, 0);
    int length = snprintf(NULL, 0, "%d", number) + 1;
    char* result = malloc(length * sizeof(char));

    snprintf(result, length, "%d", number);
    send_socket(client->control_fd, result);
    free(result);
}

void send_freq(clients_s *client, server_t *server)
{
    int length = snprintf(NULL, 0, "sgt %d", server->config->freq) + 1;
    char* result = malloc(length * sizeof(char));

    snprintf(result, length, "sgt %d", server->config->freq);
    send_socket(client->control_fd, result);
    free(result);
}

void send_team(clients_s* client, server_t *server)
{
    int length = 0;
    char* result = NULL;
    char **nameX = server->config->nameX;

    for (int i = 0; nameX[i]; i++) {
        length = snprintf(NULL, 0, "tna %s", nameX[i]) + 1;
        result = malloc((length) * sizeof(char));
        snprintf(result, length, "tna %s", nameX[i]);
        send_socket(client->control_fd, result);
        free(result);
    }
}

void send_sst(char **cmd, clients_s *client, server_t *server)
{
    server->config->freq = atoi(cmd[1]);
    send_freq(client, server);
}
