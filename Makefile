all:
	gcc -o ft_malcolm src/libft/*.c src/ft_malcolm.c

run:
	sudo ./ft_malcolm 172.22.0.4 a0:a0:a0:a0:a0:a0 172.22.0.3 02:42:ac:16:00:03