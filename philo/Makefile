# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/01 10:02:51 by pborrull          #+#    #+#              #
#    Updated: 2024/02/29 12:03:46 by pborrull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
RED = \033[1;31m
MAGENTA = \033[1;35m
BLUE = \033[38;5;75m
ORIGINAL = \033[0m

CFLAGS := -Wall -Werror -Wextra -MMD  #-fsanitize=thread -g

SOURCE := philo.c auxi.c actions.c init.c mutex_destroyer.c

OBJS := $(addprefix ./obj/, $(SOURCE:.c=.o))

DEPS = $(addprefix ./obj/, $(SOURCE:.c=.d))

.SILENT:

all: dir $(NAME)

dir:
	mkdir -p obj

$(NAME): $(OBJS)  
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo  "$(GREEN)[OK]       $(YELLOW)All Compiled$(ORIGINAL)"

./obj/%.o: %.c Makefile
	@$(CC) -c  $(CFLAGS) $< -o $@
	@echo "$(GREEN)[OK]       $(CYAN)Compiled$(ORIGINAL)"

clean:
	@rm -rf obj
	@rm -f $(OBJS) $(DEPS)
	@echo "$(RED)[OK]       $(BLUE)All Clean$(ORIGINAL)"

fclean: clean
	@rm -rf obj
	@rm -f $(OBJS) $(DEPS)
	@rm -rf $(NAME)
	@echo  "$(RED)[OK]       $(MAGENTA)All Very Clean$(ORIGINAL)"

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
