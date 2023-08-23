# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julmuntz <julmuntz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/22 14:01:56 by gfranque          #+#    #+#              #
#    Updated: 2023/08/23 14:20:00 by julmuntz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

###############
###	ALIAS	###
###############

SRC = ft_atoi.c ft_isalpha.c ft_itoa.c ft_memmove.c ft_putnbr_fd.c ft_strdup.c\
ft_strlcpy.c ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_memchr.c\
ft_memset.c ft_putstr_fd.c ft_striteri.c ft_strlen.c ft_strrchr.c ft_toupper.c\
ft_calloc.c ft_isdigit.c ft_memcmp.c ft_putchar_fd.c ft_split.c ft_strjoin.c\
ft_strmapi.c ft_strtrim.c ft_isalnum.c ft_isprint.c ft_memcpy.c ft_putendl_fd.c\
ft_strchr.c ft_strlcat.c ft_strncmp.c ft_substr.c\
ft_printf.c ft_putnbr_base.c ft_var2.c ft_putchar.c ft_putnbr.c ft_var.c\
get_next_line_bonus.c get_next_line_utils_bonus.c ft_isspace.c ft_free_lines.c\
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_str_is.c

INCLUDES = -I ../../headers/

SRC_DIR = source

OBJ_DIR = ../../obj

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
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@
	$(UNCOLOR)

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@$(MKDIR) $(@D)
	$(UNCOLOR)
	$(GCC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
	@echo "\033[46m\033[37m Libft \033[0m"
	$(UNCOLOR)
	$(AR) $(NAME) $(OBJS)
	@echo "\033[46m\033[37m Compilation completed \033[0m"

clean:
	$(COLORYELLOW)
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJ_BONUS_DIR)
	$(UNCOLOR)
	@echo "\033[33mClean done\033[0m"

fclean:	clean
	$(COLORYELLOW)
	$(RM) $(NAME) $(NAME_BONUS)
	$(UNCOLOR)
	@echo "\033[33mFclean done\033[0m"

re:
	$(MAKE) fclean
	$(MAKE) -j all

m: all clean

.PHONY: all clean fclean re m bonus
