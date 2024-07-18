/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** handle_time
*/

#include "../include/zappy.h"

void exec_order(clients_s *client, server_t *server, struct timespec stop)
{
    queue_s *list_tmp = NULL;
    queue_s *list = client->list;
    time_t elapsed_ms;

    if (!list)
        return;
    elapsed_ms = (stop.tv_nsec - list->startTime.tv_nsec) / 1000
    + (stop.tv_sec - list->startTime.tv_sec) * 1000000;
    if ((int)((float)((float)list->cmd.settime
    / server->config->freq) * 1000000) <= elapsed_ms) {
        list->cmd.exec(server, client, list->cmd_args);
        client->list = remove_queue(client->list, list);
        client->list ? clock_gettime(4, &client->list->startTime) : 0;
    }
}

int action_dead_use(clients_s *client, server_t *server, struct timespec stop)
{
    clients_s *tmp;

    if (client->inventory.objects[food] != 0) {
        client->inventory.objects[food_eaten]++;
        client->inventory.objects[food]--;
    } else if (client->inventory.objects[food] == 0) {
        tmp = client->next;
        send_socket(client->control_fd, "dead");
        client = event_disconnection(server, client);
        loop_hdl_time(tmp, server, stop);
        return 1;
    }
    return 0;
}

void loop_hdl_time(clients_s *client, server_t *server, struct timespec stop)
{
    time_t elapsed_ms;

    if (!client || client->mode <= 0)
        return client ? loop_hdl_time(client->next, server, stop) : 0;
    elapsed_ms = (stop.tv_nsec - client->start.tv_nsec) / 1000
    + (stop.tv_sec - client->start.tv_sec) * 1000000;
    if (elapsed_ms >= (int)((float) ((float)((float)((float)1260.0
    / server->config->freq) / 10) * client->inventory.objects[food_eaten])
    * 1000000) && action_dead_use(client, server, stop))
        return;
    exec_order(client, server, stop);
    return loop_hdl_time(client->next, server, stop);
}

void map_time_spawn_objects(server_t *server, struct timespec stop)
{
    time_t elapsed_ms = (stop.tv_nsec
    - server->chrono_time_spawn_object.tv_nsec) / 1000
    + (stop.tv_sec - server->chrono_time_spawn_object.tv_sec) * 1000000;

    if (server->time_before_object_spawn > 1) {
        elapsed_ms >= (int)((float)((float)20.0 / server->config->freq)
        * 1000000) ? server->time_before_object_spawn-- : 0;
        return;
    }
    clock_gettime(4, &server->chrono_time_spawn_object);
    server->time_before_object_spawn = TIME_BEFORE_OBJECT_SPAWN;
    check_and_spawn(server);
}

void handle_time(server_t *server)
{
    struct timespec stop;

    clock_gettime(4, &stop);
    loop_hdl_time(server->clients, server, stop);
    map_time_spawn_objects(server, stop);
}
