# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmendes <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/10 15:08:54 by jmendes           #+#    #+#              #
#    Updated: 2021/10/18 11:04:46 by jmendes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
FLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=address
RM = rm -f

NAME = philo
INCLUDE = philo.h 

SRC =	main.c\
		action.c\
		args.c\
		time.c\
		error.c\

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	gcc	 $(OBJS) $(FLAGS) -o $(NAME)

.c.o: $(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re