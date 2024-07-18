/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** table
*/

#include "../../include/zappy.h"

int match_table(char *value, char **table, int i)
{
    if (!table[i])
        return 0;
    if (strcmp(value, table[i]) == 0)
        return i + 1;
    return match_table(value, table, ++i);
}

int check_limit_number(char **table, int width, int height)
{
    int y = atoi(table[2]);
    int x = atoi(table[1]);

    if (check_number(table[1]) && check_number(table[2])
    && height > y && y >= 0 && width > x && x >= 0)
        return 1;
    return 0;
}

char **copy_table(char **cmd_char)
{
    int table_len = len_table(cmd_char);
    char **cmd_tmp = malloc(sizeof(char *) * (table_len + 1));

    for (int i = 0; i < table_len; i++) {
        cmd_tmp[i] = malloc(sizeof(char) * (strlen(cmd_char[i]) + 1));
        strcpy(cmd_tmp[i], cmd_char[i]);
    }
    cmd_tmp[table_len] = NULL;
    return cmd_tmp;
}
