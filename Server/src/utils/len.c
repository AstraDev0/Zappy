/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** len
*/

#include "../../include/zappy.h"

int len_table(char **table)
{
    int count = 0;

    for (count = 0; table[count]; count++);
    return count;
}

int check_number(char *value)
{
    for (int i = 0; value[i]; i++) {
        if (value[i] > '9' || value[i] < '0')
            return 0;
    }
    return 1;
}
