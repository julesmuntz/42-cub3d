# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfranque <gfranque@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 16:23:53 by gfranque          #+#    #+#              #
#    Updated: 2023/08/21 16:32:55 by gfranque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pixelgameengine.a

###############
###	ALIAS	###
###############

SRC = 	circle.c		\
		game.c			\
		local_xpm.c		\
		pixels.c		\
		sprite.c		\
		utils.c			\
		xpm.c			\
		drawpixels.c	\
		key.c			\
		loop.c			\
		rectangle.c		\
		triangle.c		\
		vector.c		\

INCLUDES = -I header/ -I ../minilibx/

LIBFTINC = -I ../libft/

LIBFT = ../libft/libft.a

MLX = ../minilibx/libmlx_Linux.a

LIBRARY = -lX11 -lXext -lm

SRC_DIR = source

OBJ_DIR = objet

SRCS = $(SRC:%=$(SRC_DIR)/%)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

GCC = cc

FLAGS = -g3 -Wall -Wextra -Werror 

AR = ar rcs

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
	$(GCC) $(FLAGS) $(INCLUDES) $(LIBFTINC) -c $< -o $@
	$(UNCOLOR)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(MKDIR) $(@D)
	$(COLORCYAN)
	$(GCC) $(FLAGS) $(INCBONUS) $(LIBFTINC) -c $< -o $@
	$(UNCOLOR)

$(NAME):	$(OBJS)
	@echo "\033[46m\033[37m PixelGameEngine \033[0m"
	$(COLORGREEN)
	make -C ../libft
	$(UNCOLOR)
	make -C ../minilibx
	$(COLORCYAN)
	$(AR) $(NAME) $(OBJS)
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
	@make fclean -C ../libft
	$(UNCOLOR)
	@make clean -C ../minilibx
	$(COLORYELLOW)
	$(RM) $(NAME) $(NAME_BONUS)
	$(UNCOLOR)
	@echo "\033[33mFclean done\033[0m"

re:
	$(MAKE) fclean
	$(MAKE) -j all

m: all clean

.PHONY: all clean fclean re m bonus
