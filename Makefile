# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 11:43:30 by wricky-t          #+#    #+#              #
#    Updated: 2022/11/04 20:57:19 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

NAME		:= so_long

CC			:= gcc

CFLAGS		:= -Wall -Wextra -Werror

# debug mode, use with "make DB=1"
ifeq ($(DB), 1)
	CFLAGS += -g3 -fsanitize=address
endif

SRC_PATH	:= srcs

OBJ_PATH	:= objs

MLX_PATH	:= mlx

LIB_PATH	:= lib42

INC_PATH	:= include

INCFLAGS	:= -I $(INC_PATH) -I $(MLX_PATH) -I $(LIB_PATH)

STATLIB		:= $(LIB_PATH)/*.a

MLXFLAGS	:= -Lmlx -lmlx -framework OpenGL -framework AppKit

#------------------------------------------------------------------------------#
#   UTILS                                                                      #
#------------------------------------------------------------------------------#

RM			:= rm -rf

NORM		:= norminette

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
#   PROGRAM'S SCRS                                                             #
#------------------------------------------------------------------------------#

SRCS		:= so_long.c \
			   init/utils_init.c \
			   init/add_entity.c \
		   	   init/add_object.c \
		   	   map/map_aesthetic.c \
		   	   map/map_format.c \
		   	   map/map_format_utils.c \
		   	   map/map_pathfinder.c \
		   	   map/map_validator.c \
		   	   image/copy_image.c \
		   	   image/draw_base.c \
		   	   image/draw_entity.c \
		   	   image/draw_map.c \
		   	   image/draw_ui.c \
		   	   image/draw_utils.c \
		   	   image/img_db_init.c \
		   	   render/update_frame.c \
		   	   render/update_stats.c \
		   	   mechanism/general_mechanism.c \
		   	   mechanism/player_mechanism.c \
		   	   mechanism/skeleton_mechanism.c \
		   	   mechanism/skeleton_helper.c \
		   	   free/free.c \
			   free/exit_game.c

SRCS	:= $(SRCS:%=$(SRC_PATH)/%)

OBJS	:= $(SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)

#------------------------------------------------------------------------------#
#   RECIPE                                                                     #
#------------------------------------------------------------------------------#

all: $(NAME)
	@echo "   $(WH)┏━┓"
	@echo "   ┃━╋━┳┓┏━┳━┳┳━┓"
	@echo "   ┣━┃$(GR)╋$(WH)┃┗┫$(BL)╋$(WH)┃┃┃┃$(YL)╋$(WH)┃"
	@echo "   ┗━┻━┻━┻━┻┻━╋┓┃"
	@echo "   ╋╋╋╋╋╋╋╋╋╋╋┗━┛\n$(DF)"
	@echo "$(GR)╔═   $(WH)START GAME$(YL)   ═╗"
	@echo "$(GR)║ $(WH)./so_long [.ber]$(YL) ║"
	@echo "$(GR)║        $(BL)OR       $(YL) ║"
	@echo "$(GR)║     $(WH)make play   $(YL) ║"
	@echo "$(GR)╚═               $(YL) ═╝$(DF)"

$(NAME): $(OBJS)
	@clear
	@echo "$(YL)↻ creating $(NAME)...$(DF)"
	@make bonus -C $(LIB_PATH)
	@$(CC) $(OBJS) $(CFLAGS) $(MLXFLAGS) $(STATLIB) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@
	@echo "$(GR)↻ compiling $(notdir $<)$(DF)"

clean:
	@make clean -C $(LIB_PATH)
	@$(RM) $(OBJ_PATH)
	@echo "$(YL)✗ removed $(OBJ_PATH)$(DF)"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@$(RM) $(NAME)
	@echo "$(YL)✗ removed $(NAME)$(DF)"

re: fclean all

check: $(SRCS)
	@clear
	@$(NORM) $(SRCS) $(INC_PATH) assets

checkall: $(SRCS)
	@clear
	@$(NORM) $(SRCS) $(INC_PATH) $(LIB_PATH)

checkheader:
	@clear
	@$(NORM) $(INC_PATH) assets

.PHONY:
	clean fclean re
