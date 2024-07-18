/*
** EPITECH PROJECT, 2023
** B-NWP-400-BER-4-1-myftp-matthis.brocheton
** File description:
** select
*/

#include "../include/zappy.h"

static void handle_timeval(server_t *server, struct timespec *start)
{
    struct timespec stop;
    time_t elapsed_ms;
    time_t elapsed_ms_stop;

    clock_gettime(4, &stop);
    elapsed_ms = (stop.tv_nsec - start->tv_nsec) / 1000
    + (stop.tv_sec - start->tv_sec) * 1000000;
    if ((server->current_timeval.tv_sec == 0
    && server->current_timeval.tv_usec == 0)
        || server->current_timeval.tv_usec <= elapsed_ms) {
        elapsed_ms_stop = elapsed_ms - server->current_timeval.tv_usec;
        memcpy(&server->current_timeval, &server->timeval,
        sizeof(struct timeval));
        server->current_timeval.tv_usec = server->current_timeval.tv_usec
        > elapsed_ms_stop
        ? server->current_timeval.tv_usec -= elapsed_ms_stop : 0;
    } else {
        server->current_timeval.tv_usec -= elapsed_ms;
    }
}

void child_sockets_wait_activity(server_t *server)
{
    clients_s *save = server->clients;
    int max_sd = 0;

    FD_ZERO(&server->readfds);
    FD_SET(server->control_fd, &server->readfds);
    max_sd = server->control_fd;
    while (save != NULL) {
        server->sd = save->control_fd;
        server->sd > 0 ? FD_SET(server->sd, &server->readfds) : 0;
        server->sd > max_sd ? max_sd = server->sd : 0;
        save = save->next;
    }
    handle_timeval(server, &server->start);
    (select(max_sd + 1, &server->readfds, NULL, NULL,
    &server->current_timeval) < 0) && (errno != EINTR) ?
    error_server("select", server->control_fd) : 0;
    clock_gettime(4, &server->start);
}
