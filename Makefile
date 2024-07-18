##
## EPITECH PROJECT, 2023
## B-YEP-400-BER-4-1-zappy-matthis.brocheton
## File description:
## Makefile
##

comp:
		make -C ./Graphical
		make -C ./AI
		make -C ./Server

all:	comp

clean:
		make clean -C ./Graphical
		make clean -C ./AI
		make clean -C ./Server

fclean:	clean
		make fclean -C ./Graphical
		make fclean -C ./AI
		make fclean -C ./Server

re:		fclean all

.PHONY:	re fclean clean all