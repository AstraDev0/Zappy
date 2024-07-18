##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## compile
##

SRC_DIR		= 	./

SRC	=	$(shell find $(SRC_DIR) -name '*.cpp')

OBJ	=	$(SRC:.cpp=.o)

NAME	=	zappy_gui

TESTS_DIR	=	tests/

TESTS	=	$(TESTS_DIR)

UNIT_TESTS	=	unit_tests

CRITFLAG	=	--coverage	\
				-lcriterion

CFLAG	=	-std=gnu17	\
			-Wall		\
			-Wextra		\
			-Werror		\
			-fPIC		\
			-g3

LDFLAGS	=	-lsfml-graphics	\
			-lsfml-window	\
			-lsfml-system

MAKEFLAG	=	fclean

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CFLAG) $(LDFLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) *~
	$(RM) \#*
	$(RM) .#*
	$(RM) *.gc*

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

$(UNIT_TESTS):	re
	g++ -o $(UNIT_TESTS) $(TESTS) $(OBJ)	\
	$(CFLAG) $(CRITFLAG) $(LDFLAGS)

tests_run:	$(UNIT_TESTS)
	./$(UNIT_TESTS)

.PHONY:	tests_run unit_tests re fclean clean debug all