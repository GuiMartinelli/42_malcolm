# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:38:06 by guferrei          #+#    #+#              #
#    Updated: 2024/05/06 15:40:59 by guferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all:
	gcc -o ft_malcolm src/libft/*.c src/cli/*.c src/interface/interface.c src/signal/signal.c src/network/*.c src/display/*.c  src/utils/*.c src/ft_malcolm.c

docker:
	docker-compose up -d --build

clean:
	rm -f ft_malcolm

fclean: clean
	docker image prune -a && docker system prune -f

re: clean all

run:
	sudo ./ft_malcolm 172.22.0.4 a0:a0:a0:a0:a0:a0 172.22.0.3 02:42:ac:16:00:03
