/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** error
*/

#include "../../include/zappy.h"

int error_cmd(server_t *server, clients_s *client, char **cmd)
{
    return send_socket(client->control_fd, "ko");
}
