# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 16:23:53 by gfranque          #+#    #+#              #
#    Updated: 2023/09/02 17:24:07 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D-bonus

###############
###	ALIAS	###
###############

SRC = 	cub3d.c				\
		mapping.c			\
		utilities.c			\
		player.c			\
		colors.c			\
		check_file.c		\
		textures.c			\
		raycast.c			\
		raycast_texture.c	\
		movement.c			\
		movement2.c			\
		check_map.c			\
		portal.c			\

# SRC_BONUS =	cub3d.c			\

INCLUDES = -I ./headers/ -I ./libs/mlx/

LIBFT = ./libs/libft/libft.a

PGE = ./libs/pge/pixelgameengine.a

MLX = ./libs/mlx/libmlx_Linux.a

LIBRARY = -lX11 -lXext -lm

SRC_DIR = source

SRC_BONUS_DIR = source

OBJ_DIR = obj

OBJ_BONUS_DIR = obj

SRCS = $(SRC:%=$(SRC_DIR)/%)

SRCS_BONUS = $(SRC_BONUS:%=$(SRC_BONUS_DIR)/%)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_BONUS = $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

GCC = cc

FLAGS = -Wall -Wextra -Werror -g3

RM = rm -rf

MKDIR = mkdir -p

###############
### COLORS	###
###############

COLORGREEN = @echo -n "\033[92m"

COLORCYAN = @echo -n "\033[36m"

COLORYELLOW = @echo -n "\033[33m"

UNCOLOR = @echo -n "\033[0m"

RESET = \033[0m

WHITE = \033[47m

ORANGE = \033[41m

BRUN = \033[43m

BLACK = \033[100m

###############
###	RULES	###
###############

all:	$(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(MKDIR) $(@D)
	$(COLORCYAN)
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@
	$(UNCOLOR)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(MKDIR) $(@D)
	$(COLORCYAN)
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@
	$(UNCOLOR)

$(NAME):	$(OBJS)
	@echo "\033[46m\033[37m Cub3D \033[0m"
	$(COLORGREEN)
	make -C ./libs/libft
	make -C ./libs/pge
	$(UNCOLOR)
	make -C ./libs/mlx
	$(COLORCYAN)
	$(GCC) $(FLAGS) -o $(NAME) $(INCLUDES) $(OBJS) $(PGE) $(LIBFT) $(MLX) $(LIBRARY)
	$(UNCOLOR)
	@echo "\033[46m\033[37m Compilation completed \033[0m"

clean:
	$(COLORYELLOW)
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_BONUS_DIR)
	$(UNCOLOR)
	@echo "\033[33mClean done\033[0m"

fclean:	clean
	$(COLORYELLOW)
	@make fclean -C ./libs/libft
	@make fclean -C ./libs/pge
	$(UNCOLOR)
	@make clean -C ./libs/mlx
	$(COLORYELLOW)
	$(RM) $(NAME) $(NAME_BONUS)
	$(UNCOLOR)
	@echo "\033[33mFclean done\033[0m"

re:
	$(MAKE) fclean
	$(MAKE) -j all

bonus:	$(OBJS_BONUS)
	@echo "\033[46m\033[37m Cub3D \033[0m"
	$(COLORGREEN)
	make -C ./libs/libft
	make -C ./libs/pge
	$(UNCOLOR)
	make -C ./libs/mlx
	$(COLORCYAN)
	$(GCC) $(FLAGS) -o $(NAME_BONUS) $(INCLUDES) $(OBJS_BONUS) $(PGE) $(LIBFT) $(MLX) $(LIBRARY)
	$(UNCOLOR)
	@echo "\033[46m\033[37m Compilation completed \033[0m"

m: all clean

.PHONY: all clean fclean re m bonus
