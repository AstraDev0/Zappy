/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** node_client
*/

#include "../include/zappy.h"

void delete_clients(clients_s *clients)
{
    clients_s *tmp;

    if (!clients)
        return;
    tmp = clients->next;
    free_client_detail(clients);
    delete_clients(tmp);
}

clients_s *delete_client(server_t *server, clients_s *client_delete)
{
    clients_s *save = client_delete;

    if (server->clients == client_delete && !client_delete->next) {
        server->clients = NULL;
        free_client_detail(client_delete);
        return NULL;
    }
    if (server->clients == client_delete && client_delete->next) {
        server->clients = client_delete->next;
        free_client_detail(client_delete);
        return server->clients;
    }
    save = client_delete->prec;
    save->next = client_delete->next;
    free_client_detail(client_delete);
    return save;
}

clients_s *add_client_next(clients_s *clients, clients_s *client,
clients_s *save)
{
    for (int i = 0; i < 9; i++)
        client->inventory.objects[i] = 0;
    client->inventory.objects[food_eaten] = 1;
    client->inventory.objects[food] = 9;
    if (clients == NULL)
        return client;
    while (clients->next != NULL)
        clients = clients->next;
    client->prec = clients;
    clients->next = client;
    return save;
}

clients_s *add_client(server_t *server, char *addr_ip,
int port, int new_socket)
{
    clients_s *clients = server->clients;
    clients_s *save = clients;
    clients_s *client = malloc(sizeof(clients_s));

    client->control_fd = new_socket;
    client->port = port;
    client->ip_addr = addr_ip;
    client->mode = MODE_NOTHING;
    client->pst_player = NULL;
    client->level = 1;
    client->from_egg = 0;
    client->team = NULL;
    client->list = NULL;
    client->next = NULL;
    client->prec = NULL;
    return add_client_next(clients, client, save);
}

void clear(server_t *server)
{
    delete_clients(server->clients);
    FD_CLR(server->control_fd,
    &server->readfds);
    close(server->control_fd);
    shutdown(server->control_fd, SHUT_RDWR);
    free_team(server->config->team);
    map_free(server->config->map);
    free_config(server);
}
