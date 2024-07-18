/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** client
*/

#include "../include/zappy.h"

void clients_connection(server_t *server, opt_t *config)
{
    int port = 0;
    char *addr_ip;
    int new_socket = 0;

    if (FD_ISSET(server->control_fd, &server->readfds)) {
        if ((new_socket = accept(server->control_fd,
        (struct sockaddr *)&server->address,
        (socklen_t *)&server->addrlen)) < 0) {
            perror("accept");
            exit(84);
        }
        addr_ip = inet_ntoa(server->address.sin_addr);
        port = ntohs(server->address.sin_port);
        send_socket(new_socket, "WELCOME");
        server->clients = add_client(server, addr_ip, port, new_socket);
        printf("Client connected [%s:%d]\n", addr_ip, port);
    }
}

clients_s *event_disconnection(server_t *server, clients_s *client)
{
    send_pdi(server->clients, client);
    printf("Client disconnected [%s:%d]\n",
    client->ip_addr, client->port);
    client->pst_player ? server->config->map[client->pst_player->Y]
    [client->pst_player->X]->objects[player]-- : 0;
    client->from_egg ? server->config->team[client->mode - 1]->clientsNb-- : 0;
    close(client->control_fd);
    return delete_client(server, client);
}

clients_s *event_client_and_disconnection(server_t *server, clients_s *client)
{
    char buffer[MAXDATASIZE] = { 0 };

    if ((server->valread = read(server->sd, buffer,
    MAXDATASIZE)) == 0) {
        return event_disconnection(server, client);
    } else {
        buffer[server->valread - 1] = '\0';
        (server->valread - 1) != 0 ?
        get_order(buffer, client, server) : 0;
    }
    return client;
}

void loop_check_disconnection(server_t *server)
{
    clients_s *clients = server->clients;

    while (clients != NULL) {
        server->sd = clients->control_fd;
        if (FD_ISSET(server->sd, &server->readfds))
            clients = event_client_and_disconnection(server, clients);
        clients = clients && clients->next ? clients->next : NULL;
    }
}

void wait_client(server_t *server)
{
    if (listen(server->control_fd, 3) < 0)
        error_server("listen", server->control_fd);
}
