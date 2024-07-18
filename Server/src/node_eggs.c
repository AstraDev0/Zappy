/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** node_eggs
*/

#include "../include/zappy.h"

void remove_eggs(eggs_t *eggs)
{
    eggs_t *eggs_tmp;

    if (!eggs)
        return;
    eggs_tmp = eggs->next;
    free(eggs);
    remove_eggs(eggs_tmp);
}

eggs_t *add_egg(eggs_t *eggs, pst_t *pst, int num, int id_player)
{
    eggs_t *eggs_tmp = malloc(sizeof(eggs_t));
    eggs_t *save = eggs;

    eggs_tmp->id_egg = num;
    eggs_tmp->player_id = id_player;
    eggs_tmp->pst = (pst_t){pst->X, pst->Y, random_number(1, 4)};
    eggs_tmp->next = NULL;
    eggs_tmp->prec = NULL;
    if (!eggs)
        return eggs_tmp;
    while (eggs->next)
        eggs = eggs->next;
    eggs->next = eggs_tmp;
    eggs_tmp->prec = eggs;
    return save;
}

eggs_t *remove_egg(eggs_t *eggs, eggs_t *egg_to_delete)
{
    eggs_t *save = egg_to_delete;

    if (eggs == egg_to_delete && !egg_to_delete->next) {
        free(egg_to_delete);
        return NULL;
    }
    if (eggs == egg_to_delete && egg_to_delete->next) {
        eggs = egg_to_delete->next;
        free(egg_to_delete);
        return eggs;
    }
    save = egg_to_delete->prec;
    save->next = egg_to_delete->next;
    free(egg_to_delete);
    return save;
}
