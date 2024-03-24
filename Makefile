# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/24 20:34:39 by agusheredia       #+#    #+#              #
#    Updated: 2024/03/24 20:41:25 by agusheredia      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Wall -Werror -Wextra -g -fsanitize='address,undefined'
SRC =

HEADER = philo.h 

#Objects
OBJ_DIR = obj
OBJECTS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))

INCLUDES = -I includes

# Colors
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
DEFAULT = \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: srcs/%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) $(INCLUDES) -c -o $@ $<
	@echo "$(GREEN)$(NAME): $(YELLOW)Compiling $<$(DEFAULT)"

$(NAME): $(OBJECTS)
	@$(CC) $(FLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@make -C $(LIBFT_PATH) clean
	@make -C $(READLINE_PATH) clean
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY: all re clean fclean subsystems
