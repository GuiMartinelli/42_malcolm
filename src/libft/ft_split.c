/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 20:18:13 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/02 20:09:44 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	matrix_size(char const *s, unsigned char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s != c && *s != '\0')
				s++;
		}
		else if (*s == c)
			s++;
	}
	count++;
	return (count);
}

int	strlenchr(char	*s, char c)
{
	int	size;

	size = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		size++;
	}
	size++;
	return (size);
}

char	*str_cpy(char *src, char *dest, char c)
{
	while (*src != c && *src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	if (*src == '\0')
		return (src);
	src++;
	return (src);
}

char	**ft_split(char const *s, char c)
{
	int		str;
	char	**ptr;
	int		cont;
	int		size;

	cont = 0;
	str = matrix_size(s, (unsigned char)c);
	ptr = malloc(str * sizeof(char *));
	if (ptr == NULL)
		return (NULL);
	while (cont < (str - 1))
	{
		if (*s == c)
			s++;
		else
		{
			size = strlenchr((char *)s, c);
			ptr[cont] = (char *)malloc(size * sizeof(char));
			s = str_cpy((char *)s, ptr[cont], c);
			cont++;
		}
	}
	ptr[cont] = (char *) NULL;
	return (ptr);
}
