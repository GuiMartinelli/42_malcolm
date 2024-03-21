/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:39:57 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/03 20:11:28 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*ptr;
	int			c;
	size_t		size;

	c = 0;
	size = ft_strlen((char *)s);
	ptr = malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	while (*(s + c))
	{
		*(ptr + c) = f(c, *(s + c));
		c++;
	}
	*(ptr + c) = '\0';
	return (ptr);
}
