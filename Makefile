# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/02 10:46:26 by wricky-t          #+#    #+#              #
#    Updated: 2022/09/15 20:09:36 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= so_long

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -I$(MLX_DIR) -I$(INC) -g -fsanitize=address
MLXFLAGS:= -lmlx -framework OpenGL -framework AppKit
SRC_DIR	:= srcs
OBJ_DIR	:= objs
MLX_DIR	:= mlx
SRCS	:= so_long.c \
		   init/entity_init.c \
		   init/player_init.c \
		   init/utils_init.c \
		   init/vector_init.c \
		   init/window_init.c
SRCS	:= $(SRCS:%=$(SRC_DIR)/%)
OBJS	:= $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC		:= include
LIB42	:= lib42
LIB42_SL:= $(LIB42)/lib42.a

# $(SRCS:%=$(SRC_DIR)/%):
# Each item of SRCS represented by % becomes itself % plus the $(SRC_DIR)/
# so let's say the item test.c would turned into srcs/test.c

#------------------------------------------------------------------------------#
#   UTILS                                                                      #
#------------------------------------------------------------------------------#
RM		:= rm -rf
NORM	:= norminette

#------------------------------------------------------------------------------#
#   STYLING                                                                    #
#------------------------------------------------------------------------------#
GR 		:= \033[1;92m
WH		:= \033[1;37m
BL		:= \033[1;34m
YL		:= \033[1;33m
DF		:= \033[0m
BK		:= \033[33;5m

#------------------------------------------------------------------------------#
#   RECIPE                                                                     #
#------------------------------------------------------------------------------#

all: $(NAME)
	@echo "  $(WH)┏━┓"
	@echo "  ┃━╋━┳┓┏━┳━┳┳━┓"
	@echo "  ┣━┃$(GR)╋$(WH)┃┗┫$(BL)╋$(WH)┃┃┃┃$(YL)╋$(WH)┃"
	@echo "  ┗━┻━┻━┻━┻┻━╋┓┃"
	@echo "  ╋╋╋╋╋╋╋╋╋╋╋┗━┛\n$(DF)"
	@echo "$(GR)=== $(WH)START GAME $(YL)==="
	@echo "$(WH) ./so_long [map]"
	@echo "$(GR)======$(BL)======$(YL)======$(DF)"

$(NAME): $(OBJS) lib
	@$(CC) $(CFLAGS) $(MLXFLAGS) $(OBJS) -o $(NAME) $(LIB42_SL)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@clear
	@-[ ! -d $(@D) ] && mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GR)↻ compiling...$(DF)"

lib:
	@make all -C $(LIB42)

clean:
	@-[ -d $(OBJ_DIR) ] && $(RM) $(OBJ_DIR)
	@clear
	@echo "$(YL)✗ removed $(OBJ_DIR)$(DF)"

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB42)
	@clear
	@echo "$(YL)✗ removed $(NAME)$(DF)"

re: fclean all

check: $(SRCS)
	@clear
	@$(NORM) $(SRCS)

check_all: check
	@clear
	@$(NORM) $(INC) $(LIB42)

# .SILENT:
.PHONY: all clean fclean re check so_long

# -[ ! -d $(@D) ] && mkdir -p $(@D)
# || |  |    |    |  |      |    |
# +|-|--|----|----|--|------|----|- suppress make non-zero status errors
#  +-|--|----|----|--|------|----|- if
#    +--|----|----|--|------|----|- doesn't exist
#       +----|----|--|------|----|- as a directory
#            +----|--|------|----|- the dir part of the target filename
#                 +--|------|----|- then
#                    +------|----|- create the directory
#                           +----|- and the parents directories if missing
#                                +- of the dir part of the target filename
