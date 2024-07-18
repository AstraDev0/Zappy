/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** random
*/

#include "../../include/zappy.h"

int random_number(int min, int max)
{
    return (min + rand() % (max - min + 1));
}

int random_port(void)
{
    return random_number(49152, 65535);
}

pst_t *random_pst(int height, int width)
{
    pst_t *position = malloc(sizeof(pst_t));

    position->O = random_number(1, 4);
    position->X = random_number(0, width - 1);
    position->Y = random_number(0, height - 1);
    return position;
}
