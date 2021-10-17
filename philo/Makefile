NAME			= philo

FLAGS			= -Wall -Wextra -Werror #-g -fsanitize=thread
OPT				= -O3 -flto -Ofast -ffast-math -march=native
LIBFT			= -L libft -lft

OBJS_DIR		= objects
INCLUDES		= includes
LIBFT_PATH		= libft

SRCS		= \
philosophers.c \
utils.c \
error.c \
check_status.c \
init.c \
clear.c \
actions.c


FILES			= sources
FOLDERS			=
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all:				$(NAME)

$(NAME):			$(OBJS)
						@mkdir -p $(OBJS_DIR)
						@gcc $(FLAGS) $^ -o $@
						@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUE): $(GREEN)Compiled [√]$(RESET)\n"

$(OBJS_DIR)/%.o:	$(FILES)/%.c $(addprefix $(INCLUDES)/, philosophers.h)
						@mkdir -p $(OBJS_DIR)
						@gcc $(FLAGS) -I$(INCLUDES) -c $< -o $@
						@printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUE): $(PURPLE)$<$(RESET)"

clean:
						@rm -f $(OBJS)
						@rm -rf $(OBJS_DIR)

fclean:				clean
						@rm -f $(NAME)

re:					fclean all

.PHONY:				all clean fclean re

BLACK			=	\033[0;30m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
ORANGE			=	\033[0;33m
BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
CYAN			=	\033[0;36m
LIGHT_GRAY		=	\033[0;37m
DARK_GRAY		=	\033[1;30m
LIGHT_RED		=	\033[1;31m
LIGHT_GREEN		=	\033[1;32m
YELLOW			=	\033[1;33m
LIGHT_BLUE		=	\033[1;34m
LIGHT_PURPLE	=	\033[1;35m
LIGHT_CYAN		=	\033[1;36m
WHITE			=	\033[1;37m
NO_COLOR		=	\033[0m
