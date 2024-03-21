/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 19:30:57 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/04 17:31:36 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		c;
	size_t	size;

	c = 0;
	size = ft_strlen((char *)s);
	if (len == 0 || (size_t)start > len || start > size)
	{
		ptr = ft_calloc(1, sizeof(char));
		return (ptr);
	}
	if ((size + start) < len)
		ptr = malloc((size + 1) * sizeof(char));
	else
		ptr = malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	s = s + start;
	while (c < (int)len && *(s + c) != '\0')
	{
		*(ptr + c) = *(char *)(s + c);
		c++;
	}
	*(ptr + c) = '\0';
	return (ptr);
}
