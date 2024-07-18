/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** str
*/

#include "../../include/zappy.h"

static const command_t resource[] = {
    { "food", NULL, 0 }, { "linemate", NULL, 0 }, { "deraumere", NULL, 0 },
    { "sibur", NULL, 0 }, { "mendiane", NULL, 0 },
    { "phiras", NULL, 0 }, { "thystame", NULL, 0 }, { "player", NULL, 0 }
    };

int vlt_btw(int i, int size, int y_x)
{
    return (y_x + i) < 0 ? (size) + (y_x + i) : (y_x + i) > size - 1 ?
    size - (y_x + i) : (y_x + i);
}

char *add_value_to_str(char *result, const char *to_add)
{
    int length = 0;
    int len = 0;

    if (result == NULL) {
        length = snprintf(NULL, 0, "%s", to_add) + 1;
        result = malloc(length * sizeof(char));
        snprintf(result, length, "%s", to_add);
    } else {
        len = strlen(result);
        length = snprintf(NULL, 0, "%s", to_add) + 1;
        result = realloc(result, sizeof(char) * (length + len));
        snprintf(result + len, length, "%s", to_add);
    }
    return result;
}

char *process_obj_to_str(char *result, int i, map_s *map)
{
    char *new_result;
    int length = 0;

    if (map->objects[i] == 0)
        return result;
    for (int c = map->objects[i]; c > 0; c--) {
        length = snprintf(NULL, 0, " %s", resource[i].cmd)
        + 1;
        new_result = malloc(length * sizeof(char));
        snprintf(new_result, length, " %s", resource[i].cmd);
        result = add_value_to_str(result, new_result);
        free(new_result);
    }
    return result;
}

char *add_obj_to_str(char *result, map_s *map)
{
    result = process_obj_to_str(result, player, map);
    for (int i = 0; i < 7; i++)
        result = process_obj_to_str(result, i, map);
    return result;
}

char *add_id_to_str(clients_s *clients, char *result)
{
    char *buffer;
    int length = 0;

    if (!clients)
        return result;
    if (clients->mode > 0)
        return add_id_to_str(clients->next, result);
    length = snprintf(NULL, 0, " %d", clients->control_fd) + 1;
    buffer = malloc(length * sizeof(char));
    snprintf(buffer, length, " %d", clients->control_fd);
    result = add_value_to_str(result, buffer);
    free(buffer);
    return add_id_to_str(clients->next, result);
}
