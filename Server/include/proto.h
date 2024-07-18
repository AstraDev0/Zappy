/*
** EPITECH PROJECT, 2021
** project name
** File description:
** simple description
*/

#ifndef PROTO_H_
    #define PROTO_H_

int main(int ac, char **av);
void delete_clients(clients_s *clients);
clients_s *delete_client(server_t *server, clients_s *client_delete);
clients_s *add_client_next(clients_s *clients, clients_s *client,
clients_s *save);
clients_s *add_client(server_t *server, char *addr_ip,
int port, int new_socket);
void clear(server_t *server);
int check_order(char **cmd);
void parser_order_start(char **cmd, clients_s *client, server_t *server);
void get_player(clients_s *client, server_t *server);
void send_enw(server_t *server, int i);
void graphic_cmd(char **cmd, clients_s *client, server_t *server);
void handle_sigint(int sig __attribute__((unused)));
int zappy_server(server_t *init_server);
void error_server(char *message, int control_fd);
int error_cdt(char **av, int check, int cursor);
int check_n_args(char **av, int opt);
int error_arguments(char **av, int opt);
void remove_eggs(eggs_t *eggs);
eggs_t *add_egg(eggs_t *eggs, pst_t *pst, int num, int id_player);
eggs_t *remove_egg(eggs_t *eggs, eggs_t *egg_to_delete);
void loop_gnr_rcs(server_t *server, int quantity, int which, int mode_filling);
void start_generate(server_t *server, map_s *count_map, int mode_filling);
void check_and_spawn(server_t *server);
int take(server_t *server, clients_s *client, char **cmd);
int set(server_t *server, clients_s *client, char **cmd);
int send_elvt_udw(server_t *server, clients_s *client, char **cmd);
int incantation(server_t *server, clients_s *client, char **cmd);
void send_pex(server_t *server, clients_s *client);
int area_direction_clc(int o_source, int o_target);
void send_eject(clients_s *clients, clients_s *client);
int loop_ejct(server_t *server, clients_s *clients, clients_s *client, int res);
int eject(server_t *server, clients_s *client, char **cmd);
int error_cmd(server_t *server, clients_s *client, char **cmd);
char *get_stg_lvl_three(opt_t *config, pst_t *pst_player, char *result);
char *get_stg_lvl_two(opt_t *config, pst_t *pst_player, char *result);
char *get_stg_lvl_one(opt_t *config, pst_t *pst_player, char *result);
char *process_look(int step, pst_t *pst_player, opt_t *config, int lvl);
int forward(server_t *server, clients_s *client, char **cmd);
int right(server_t *server, clients_s *client, char **cmd);
int left(server_t *server, clients_s *client, char **cmd);
int laying_agg(server_t *server, clients_s *client, char **cmd);
int loop_eject_eggs(server_t *server, clients_s *client, int i, int res);
int check_position_eggs(server_t *server, clients_s *client, eggs_t *eggs);
int fork_cmd_player(server_t *server, clients_s *client, char **cmd);
int look(server_t *server, clients_s *client, char **cmd);
int inventory(server_t *server, clients_s *client, char **cmd);
int connect_nbr(server_t *server, clients_s *client, char **cmd);
int send_pbc(clients_s *client, clients_s *clients, char *msg);
int source_broatcast_clc(pst_t *src, pst_t *target);
void send_broadcast(clients_s *clients, clients_s *client, char *msg);
int broadcast(server_t *server, clients_s *client, char **cmd);
int check_ply_tl(clients_s *clients, clients_s *client, int nbr_plys);
int check_tile_rsc(map_s *tile, map_s to_cpr);
int level_up_ict(clients_s *clients, clients_s *client, clients_s *all_clt);
void send_tile_incantation(clients_s *clients, clients_s *client, char *msg);
int check_incantation(server_t *server, clients_s *client);
int add_order(server_t *server, command_t cmd, clients_s *client, char **cmd_a);
void send_ebo(server_t *server, int count_eggs);
pst_t *spawn_to_egg(clients_s *client, server_t *server);
int init_ai(char **cmd, clients_s *client, server_t *server, int mode);
int ai_cmd(char **cmd, clients_s *client, server_t *server, int mode);
void n_option(server_t *server, char **av);
void insert_clt_nbr(server_t *server, int nbr);
int check_option(int opt, server_t *server, char **av);
int check_args(int ac, char **av, server_t *server);
void clients_connection(server_t *server, opt_t *config);
clients_s *event_disconnection(server_t *server, clients_s *client);
clients_s *event_client_and_disconnection(server_t *server, clients_s *client);
void loop_check_disconnection(server_t *server);
void wait_client(server_t *server);
void send_ppo(char **cmd, clients_s *clients, clients_s *client);
void send_plv(char **cmd, clients_s *clients, clients_s *client);
void send_pin(char **cmd, clients_s *clients, clients_s *client);
void send_pnw(clients_s *clients, clients_s *client);
void send_pdi(clients_s *clients, clients_s *client);
void send_pgt_a_pdr(clients_s *client, server_t *server, int rsc_num, int mode);
void send_pie(clients_s *client, clients_s *clients, int res);
int end_game(clients_s *client, clients_s *clients);
void send_pic(server_t *server, clients_s *client);
void send_client_nb(clients_s *client, server_t *server);
void send_freq(clients_s *client, server_t *server);
void send_team(clients_s* client, server_t *server);
void send_sst(char **cmd, clients_s *client, server_t *server);
char *loop_parser_map(int x, int y, map_s ***map);
void send_map_mode_filling(int x, int y, map_s ***map, clients_s* clients);
void send_map(clients_s* client, server_t *server);
void send_map_size(clients_s *client, server_t *server, int msz);
void get_tile_map(char **cmd, clients_s *client, server_t *server);
void exec_order(clients_s *client, server_t *server, struct timespec stop);
int action_dead_use(clients_s *client, server_t *server, struct timespec stop);
void loop_hdl_time(clients_s *client, server_t *server, struct timespec stop);
void map_time_spawn_objects(server_t *server, struct timespec stop);
void handle_time(server_t *server);
void loop_insert_height(map_s ***map, int height, int width, int y);
void init_map(server_t *server);
void send_map_graphic(clients_s* clients, server_t *server);
void init_socket(server_t *server, int port);
server_t init_zappy_server_next(server_t server, opt_t *config);
server_t init_zappy_server(void);
clients_s *get_client_w_number(int num, clients_s *clients);
int place_client_team(clients_s *clients, char *team, int i);
void remove_queues(queue_s *queue);
queue_s *add_queue(queue_s *queue, command_t cmd, char **cmd_args);
queue_s *remove_queue(queue_s *queue, queue_s *queue_to_delete);
void child_sockets_wait_activity(server_t *server);
int random_number(int min, int max);
int random_port(void);
pst_t *random_pst(int height, int width);
void table_free(char **table);
void map_free(map_s ***map);
void free_config(server_t *server);
void free_client_detail(clients_s *client);
void free_team(team_t **teams);
int match_table(char *value, char **table, int i);
int check_limit_number(char **table, int width, int height);
char **copy_table(char **cmd_char);
int vlt_btw(int i, int size, int y_x);
char *add_value_to_str(char *result, const char *to_add);
char *process_obj_to_str(char *result, int i, map_s *map);
char *add_obj_to_str(char *result, map_s *map);
char *add_id_to_str(clients_s *clients, char *result);
int check_match(char c, char *separator, int count);
int check_separator(char *str, char *separator, int v);
int count_sprt(char *str, char *separator, int col, char **result);
char **separate_table(char **result, char *str, char *separator, int count_st);
char **my_split(char *str, char *separator);
int len_table(char **table);
int check_number(char *value);
void get_order(char *order, clients_s *client, server_t *server);
int send_socket(int sd, char *msg);
int send_socket_graphic_mode(clients_s* clients, char *result);
int usage(void);

#endif /* PROTO_H_ */
