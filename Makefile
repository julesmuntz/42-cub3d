# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 16:23:53 by gfranque          #+#    #+#              #
#    Updated: 2023/07/27 11:51:42 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub

NAME_BONUS = Cub

###############
###	ALIAS	###
###############

SRC = test.c

SRC_BONUS = 

INCLUDES = -I ./inc/ -I ./minilibx/

INCBONUS = -I ./inc_bonus/ -I ./minilibx/

LIBFTINC = -I ./libft/

LIBFT = ./libft/libft.a

MLX = ./minilibx/libmlx_Linux.a

LIBRARY = -lX11 -lXext -lm

SRC_DIR = .

SRC_BONUS_DIR = src_bonus

OBJ_DIR = obj

OBJ_BONUS_DIR = obj_bonus

SRCS = $(SRC:%=$(SRC_DIR)/%)

SRCS_BONUS = $(SRC_BONUS:%=$(SRC_BONUS_DIR)/%)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

OBJS_BONUS = $(SRCS_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

GCC = cc

FLAGS = -g3 -Wall -Wextra -Werror 

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
	@$(MKDIR) $(OBJ_DIR)
	$(COLORCYAN)
	$(GCC) $(FLAGS) $(INCLUDES) $(LIBFTINC) -c $< -o $@
	$(UNCOLOR)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(MKDIR) $(OBJ_BONUS_DIR)
	$(COLORCYAN)
	$(GCC) $(FLAGS) $(INCLUDES) $(LIBFTINC) -c $< -o $@
	$(UNCOLOR)

$(NAME):	$(OBJS)
	@echo "\033[46m\033[37m Cub3D \033[0m"
	$(COLORGREEN)
	make -C ./libft
	$(UNCOLOR)
	make -C ./minilibx
	$(COLORCYAN)
	$(GCC) $(FLAGS) -o $(NAME) $(INCLUDES) $(LIBFTINC) $(OBJS) $(LIBFT) $(MLX) $(LIBRARY)
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
	@make fclean -C ./libft
	$(UNCOLOR)
	@make clean -C ./minilibx
	$(COLORYELLOW)
	$(RM) $(NAME) $(NAME_BONUS)
	$(UNCOLOR)
	@echo "\033[33mFclean done\033[0m"

re:
	$(MAKE) fclean
	$(MAKE) -j all

bonus:	$(OBJS_BONUS)
	@echo "\033[46m\033[37m Fil De Fer \033[0m"
	$(COLORGREEN)
	make -C ./libft
	$(UNCOLOR)
	make -C ./minilibx
	$(COLORCYAN)
	$(GCC) $(FLAGS) -o $(NAME_BONUS) $(INCBONUS) $(LIBFTINC) $(OBJS_BONUS) $(LIBFT) $(MLX) $(LIBRARY)
	$(UNCOLOR)
	@echo "\033[46m\033[37m Compilation completed \033[0m"

m: all clean

.PHONY: all clean fclean re m bonus
