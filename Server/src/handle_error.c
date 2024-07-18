/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** handle_errors
*/

#include "../include/zappy.h"

void error_server(char *message, int control_fd)
{
    perror(message);
    close(control_fd);
    exit(84);
}

int error_cdt(char **av, int check, int cursor)
{
    for (int i = check + 1; i < cursor; i++) {
        if (strcmp(av[check], av[i]) == 0) {
            fprintf(stderr, "-n option only accepts unique team names\n");
            return 0;
        }
    }
    return 1;
}

int check_n_args(char **av, int opt)
{
    int cursor = 0;
    int interval = 0;
    int check = 0;

    for (; av[cursor] && strcmp(av[cursor], "-n") != 0; cursor++);
    for (cursor++; av[cursor] && av[cursor][0] != '-'; cursor++, interval++);
    check = cursor - interval;
    while (check <= cursor) {
        if (!error_cdt(av, check++, cursor))
            return 0;
    }
    return 1;
}

int error_arguments(char **av, int opt)
{
    if (optarg && (optarg[0] == '-' || (opt != 'n' && !check_number(optarg)))) {
        fprintf(stderr, "-%c option invalid content\n", opt);
        return 0;
    }
    if ((opt == 'f' && (atoi(optarg) < 2 || atoi(optarg) > 10000))
    || (opt == 'c' && atoi(optarg) == 0)) {
        fprintf(stderr,
        opt == 'c'
        ? "-c option only accepts integer values greater or equal to 1"
        : "-f option only accepts integer values between 2 and 10000");
        return 0;
    }
    if ((opt == 'x' || opt == 'y') && (atoi(optarg) < 10 || atoi(optarg)
    > 30)) {
        fprintf(stderr,
        "-%c option only accepts integer values between 10 and 30", opt);
        return 0;
    }
    return check_n_args(av, opt);
}
