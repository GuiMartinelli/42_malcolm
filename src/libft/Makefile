# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 22:14:47 by guferrei          #+#    #+#              #
#    Updated: 2021/07/21 13:53:59 by guferrei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FT = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
	ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
	ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
	ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
	ft_putuns_fd.c ft_putnbrX.c ft_nbrlen.c ft_put0x.c ft_putnstr.c

OBJ = $(FT:.c=.o)

CFLAGS = -Wall -Wextra -Werror

FTB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c

BO = $(FTB:.c=.o)

all: $(NAME)

$(NAME) :
	gcc ${CFLAGS} -c ${FT}
	ar rc $(NAME) ${OBJ}

bonus:
	gcc ${CFLAGS} -c ${FTB}
	ar rc ${NAME} ${BO}

fclean:	clean
	rm -f libft.a

clean:
	rm -f *.o

re:	fclean all
