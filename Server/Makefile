##
## EPITECH PROJECT, 2023
## B-YEP-400-BER-4-1-zappy-matthis.brocheton
## File description:
## Makefile
##


SRC	=	src/ai_cmd.c	\
		src/checks.c	\
		src/clients.c	\
		src/get_client_info.c	\
		src/graphic_cmd.c	\
		src/handle_error.c	\
		src/handle_time.c	\
		src/init_function.c	\
		src/init_map.c	\
		src/manage_orders.c	\
		src/node_client.c	\
		src/node_eggs.c	\
		src/node_queue.c	\
		src/ressource_gen.c	\
		src/select.c	\
		src/usage.c	\
		src/zappy_serv.c	\
		src/utils/free.c	\
		src/utils/len.c	\
		src/utils/my_split.c	\
		src/utils/random.c	\
		src/utils/str.c	\
		src/utils/table.c	\
		src/options_server/args.c	\
		src/options_server/cmd_graph.c	\
		src/options_server/map.c	\
		src/options_server/player.c	\
		src/options_ai/action.c	\
		src/options_ai/broadcast.c	\
		src/options_ai/direction.c	\
		src/options_ai/eject.c	\
		src/options_ai/error.c	\
		src/options_ai/fork.c	\
		src/options_ai/get_information.c	\
		src/options_ai/incantation.c	\
		src/options_ai/look.c	\
		main.c	\

OBJ = $(SRC:.c=.o)

NAME = zappy_server

CFLAGS = -I ./include -g3

LDFLAGS = -lm

all: $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f ./tests/*.vgcore
	rm -f ./tests/*.gcno
	rm -f ./tests/*.gcda
	rm -f ./tests/unit_tests

re: fclean all

.PHONY: re fclean clean all
