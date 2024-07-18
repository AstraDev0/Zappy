/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** zappy
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_
    #include <sys/socket.h>
    #include <stdio.h>
    #include <getopt.h>
    #include <string.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <errno.h>
    #include <signal.h>
    #include <termios.h>
    #include <math.h>
    #include <time.h>
    #define MAXDATASIZE 30000
    #define MODE_NOTHING -1
    #define MODE_GRAPHIC 0
    #define TIME_BEFORE_OBJECT_SPAWN 20
    typedef struct clients_s clients_s;
    typedef struct queue_s queue_s;
    typedef struct map_s map_s;
    typedef struct pst_t pst_t;
    typedef struct opt_t opt_t;
    typedef struct server_t server_t;
    typedef struct resource_s resource_s;
    typedef struct command_t command_t;
    typedef struct eggs_t eggs_t;
    typedef struct team_t team_t;
    typedef int (*exec_cmd)(server_t *server, clients_s *client, char **cmd);

    enum stuff {
        food,
        linemate,
        deraumere,
        sibur,
        mendiane,
        phiras,
        thystame,
        player,
        food_eaten
    };

    struct map_s {
        int objects[9];
    };

    struct pst_t {
        int X;
        int Y;
        int O;
    };

    struct eggs_t {
        int id_egg;
        int player_id;
        pst_t pst;
        eggs_t *next;
        eggs_t *prec;
    };

    struct team_t {
        int clientsNb;
        eggs_t *eggs;
    };

    struct opt_t {
        int width;
        int height;
        char **nameX;
        team_t **team;
        int freq;
        int id_eggs_ctn;
        map_s ***map;
    };

    typedef struct command_t {
        char *cmd;
        exec_cmd exec;
        int settime;
    } command_t;

    struct queue_s {
        command_t cmd;
        char **cmd_args;
        struct timespec startTime;
        queue_s *next;
        queue_s *prec;
    };

    struct clients_s {
        char *ip_addr;
        int port;
        int control_fd;
        int mode;
        pst_t *pst_player;
        map_s inventory;
        char *team;
        int level;
        int from_egg;
        queue_s *list;
        struct timespec start;
        clients_s *next;
        clients_s *prec;
    };

    struct server_t {
        struct timespec chrono_time_spawn_object;
        time_t time_before_object_spawn;
        struct timespec start;
        struct timeval timeval;
        struct timeval current_timeval;
        int control_fd;
        int valread;
        struct sockaddr_in address;
        int opt;
        int addrlen;
        int sd;
        int port;
        opt_t *config;
        fd_set readfds;
        clients_s *clients;
    };

    typedef struct resource_s {
        float density;
    } resource_s;

    #include "proto.h"
#endif /* !ZAPPY_H_ */
