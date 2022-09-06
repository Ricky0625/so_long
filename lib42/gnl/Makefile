# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/03 20:23:45 by wricky-t          #+#    #+#              #
#    Updated: 2022/09/03 20:27:50 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc

CFLAGS	:= -Wall -Werror -Wextra

SRCS	:= get_next_line.c get_next_line_utils.c

OBJS	:= $(SRCS:.c=.o)

RM		:= rm -rf

all: $(OBJS)

bonus: all

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean

re: fclean all