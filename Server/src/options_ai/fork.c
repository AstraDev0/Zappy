/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** fork
*/

#include "../../include/zappy.h"

int laying_agg(server_t *server, clients_s *client, char **cmd)
{
    int length = snprintf(NULL, 0, "pfk %d",
    client->control_fd) + 1;
    char *result = malloc(length * sizeof(char));

    snprintf(result, length, "pfk %d",
    client->control_fd);
    send_socket_graphic_mode(server->clients, result);
    free(result);
    return 0;
}

int loop_eject_eggs(server_t *server, clients_s *client, int i, int res)
{
    team_t *team = server->config->team[i];
    eggs_t *eggs = team ? team->eggs : NULL;
    eggs_t *eggs_tmp;
    int check_res = 0;

    if (!team || !eggs)
        return res;
    while (eggs) {
        eggs_tmp = eggs->next;
        check_res = check_position_eggs(server, client, eggs);
        eggs = check_res ? eggs_tmp : eggs->next;
        res = check_res ? 1 : res;
    }
    loop_eject_eggs(server, client, ++i, res);
}

int check_position_eggs(server_t *server, clients_s *client, eggs_t *eggs)
{
    int length = 0;
    char *result;

    if (eggs->pst.X != client->pst_player->X
    || eggs->pst.Y != client->pst_player->Y)
        return 0;
    length = snprintf(NULL, 0, "edi %d", eggs->id_egg) + 1;
    result = malloc(length * sizeof(char));
    snprintf(result, length, "edi %d", eggs->id_egg);
    server->config->team[client->mode - 1]->eggs
    = remove_egg(server->config->team[client->mode - 1]->eggs, eggs);
    send_socket_graphic_mode(server->clients, result);
    free(result);
    return 1;
}

int fork_cmd_player(server_t *server, clients_s *client, char **cmd)
{
    int length = 0;
    char *result;
    if (len_table(cmd) > 1)
        return send_socket(client->control_fd, "ko");
    server->config->team[client->mode - 1]->clientsNb++;
    server->config->team[client->mode - 1]->eggs
    = add_egg(server->config->team[client->mode - 1]->eggs,
    client->pst_player, server->config->id_eggs_ctn, client->control_fd);
    length = snprintf(NULL, 0, "enw %d %d %d %d\neht %d",
    server->config->id_eggs_ctn, client->control_fd,
    client->pst_player->X, client->pst_player->Y, server->config->id_eggs_ctn);
    result = malloc((length + 1) * sizeof(char));
    snprintf(result, length + 1, "enw %d %d %d %d\neht %d",
    server->config->id_eggs_ctn, client->control_fd,
    client->pst_player->X, client->pst_player->Y, server->config->id_eggs_ctn);
    send_socket_graphic_mode(server->clients, result);
    free(result);
    server->config->id_eggs_ctn++;
    send_socket(client->control_fd, "ok");
}
