all:
	gcc -o ft_malcolm src/libft/*.c src/cli/*.c src/interface/interface.c src/signal/signal.c src/network/*.c src/ft_malcolm.c

clean:
	rm -f ft_malcolm

re: clean all

run:
	sudo ./ft_malcolm 172.22.0.4 a0:a0:a0:a0:a0:a0 172.22.0.3 02:42:ac:16:00:03