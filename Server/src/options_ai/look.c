/*
** EPITECH PROJECT, 2023
** B-YEP-400-BER-4-1-zappy-matthis.brocheton
** File description:
** look
*/

#include "../../include/zappy.h"

char *get_stg_lvl_three(opt_t *config, pst_t *pst_player, char *result)
{
    int width = config->width;
    int height = config->height;
    int o = pst_player->O;
    int x = pst_player->X;
    int y = pst_player->Y;
    int y_look = o == 3 ? -3 : o == 1 ? 3 : 0;
    int x_look = o == 4 ? -3 : o == 2 ? 3 : 0;

    for (int i = -3; i < 4; i++) {
        result = add_obj_to_str(result, config->map[vlt_btw(y_look == 0 ? i
        : y_look, height, y)][vlt_btw(x_look == 0 ? i : x_look, width, x)]);
        i != 3 ? result = add_value_to_str(result, ",") : 0;
    }
}

char *get_stg_lvl_two(opt_t *config, pst_t *pst_player, char *result)
{
    int width = config->width;
    int height = config->height;
    int o = pst_player->O;
    int x = pst_player->X;
    int y = pst_player->Y;
    int y_look = o == 3 ? -2 : o == 1 ? 2 : 0;
    int x_look = o == 4 ? -2 : o == 2 ? 2 : 0;

    for (int i = -2; i < 3; i++) {
        result = add_obj_to_str(result, config->map[vlt_btw(y_look == 0 ? i
        : y_look, height, y)][vlt_btw(x_look == 0 ? i : x_look, width, x)]);
        i != 2 ? result = add_value_to_str(result, ",") : 0;
    }
}

char *get_stg_lvl_one(opt_t *config, pst_t *pst_player, char *result)
{
    int width = config->width;
    int height = config->height;
    int o = pst_player->O;
    int x = pst_player->X;
    int y = pst_player->Y;
    int y_look = o == 3 ? -1 : o == 1 ? 1 : 0;
    int x_look = o == 4 ? -1 : o == 2 ? 1 : 0;

    for (int i = -1; i < 2; i++) {
        result = add_obj_to_str(result, config->map[vlt_btw(y_look == 0 ? i
        : y_look, height, y)][vlt_btw(x_look == 0 ? i : x_look, width, x)]);
        i != 1 ? result = add_value_to_str(result, ",") : 0;
    }
    return result;
}

char *process_look(int step, pst_t *pst_player, opt_t *config, int lvl)
{
    char *result = add_value_to_str(NULL, "[");

    result = add_obj_to_str(result,
    config->map[pst_player->Y][pst_player->X]);
    result = add_value_to_str(result, ",");
    result = get_stg_lvl_one(config, pst_player, result);
    result = lvl >= 2 ? add_value_to_str(result, ",") : result;
    result = lvl >= 2 ? get_stg_lvl_two(config, pst_player, result) : result;
    result = lvl >= 3 ? add_value_to_str(result, ",") : result;
    result = lvl >= 3 ? get_stg_lvl_three(config, pst_player, result) : result;
    result = add_value_to_str(result, " ]");
    return result;
}
