# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:38:06 by guferrei          #+#    #+#              #
#    Updated: 2024/06/14 21:43:51 by guferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PATH_SRC = src
PATH_LIBFT = src/libft

NAME = ft_malcolm
LIBFT = $(addprefix $(PATH_LIBFT)/, libft.a)
MAIN = $(PATH_SRC)/ft_malcolm.c
SRC = \
	$(addprefix $(PATH_SRC)/cli/, cli.c validator_utils.c validator.c) \
	$(PATH_SRC)/display/print.c \
	$(addprefix $(PATH_SRC)/error/, error.c error_utils.c) \
	$(addprefix $(PATH_SRC)/interface/, interface.c) \
	$(addprefix $(PATH_SRC)/network/, recover_arp.c send_arp.c) \
	$(PATH_SRC)/utils/utils.c \
	$(PATH_SRC)/signal/signal.c
CC = gcc
CFLAGS = -Wall -Wextra -Werror
COMPOSE = docker-compose
DOCKER_FLAGS = up -d --build
DOCKER_IMAGES = image prune -a
DOCKER_SYSTEM = system prune -f

all: $(NAME)

$(NAME): $(LIBFT)
	$(CC) $(CFLAGS) $(MAIN) $(SRC) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(PATH_LIBFT)

clean:
	@$(MAKE) clean -C $(PATH_LIBFT)
	rm -f $(NAME)

docker:
	$(COMPOSE) $(DOCKER_FLAGS)

fclean: clean
	@$(MAKE) fclean -C $(PATH_LIBFT)
	docker $(DOCKER_IMAGES) && docker $(DOCKER_SYSTEM)

re: clean all
