# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/23 13:22:25 by dkovalen          #+#    #+#              #
#    Updated: 2017/03/13 16:28:42 by dkovalen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

FLAGS = -Wall -Wextra -Werror

LIBA = ./libft/libftprintf.a

SRC = main.c help.c help2.c rooms.c rooms2.c ways.c solve.c ants.c

SRC_O = main.o help.o help2.o rooms.o rooms2.o ways.o solve.o ants.o

all: $(SRC_O)
	@ make -C ./libft
	gcc $(FLAGS) $(SRC_O) $(LIBA) -o $(NAME)

%.o: %.c
	@gcc -c -Wall -Wextra -Werror -o $@ $<

clean:
	@ make clean -C ./libft
	rm -f $(SRC_O)

fclean: clean
	rm -f lem-in $(LIBA)

re: fclean all
