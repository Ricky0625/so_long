# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/03 19:48:16 by wricky-t          #+#    #+#              #
#    Updated: 2022/11/05 14:13:24 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= lib42.a
LIBFT	:= libft
GNL		:= gnl
GNL_OBJ	:= gnl/get_next_line.o
PRINTF	:= ft_printf
AR		:= ar rcs

all: $(LIBFT) $(PRINTF)
	@make -s all -C $(LIBFT)
	@make -s all -C $(PRINTF)
	@make -s all -C $(GNL)
	@cp $(PRINTF)/libftprintf.a ./$(NAME)
	@$(AR) $(NAME) $(GNL_OBJ)
	@make clean

bonus: $(LIBFT) $(PRINTF)
	@make -s bonus -C $(LIBFT)
	@make -s bonus -C $(PRINTF)
	@make -s bonus -C $(GNL)
	@cp $(PRINTF)/libftprintf.a ./$(NAME)
	@$(AR) $(NAME) $(GNL_OBJ)

clean: $(LIBFT) $(PRINTF)
	@make -s clean -C $(LIBFT)
	@make -s clean -C $(PRINTF)
	@make -s clean -C $(GNL)

fclean: $(LIBFT) $(PRINTF)
	@make -s fclean -C $(LIBFT)
	@make -s fclean -C $(PRINTF)
	@make -s fclean -C $(GNL)
	@$(RM) $(NAME)

re: fclean all

.SILENT: all bonus clean fclean re
.PHONY: all bonus clean fclean re
