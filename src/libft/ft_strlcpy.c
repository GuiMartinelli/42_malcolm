/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 20:47:59 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/07 20:45:30 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	c;
	size_t	s;

	c = 0;
	if (!dest || !src)
		return (0);
	s = ft_strlen(src);
	if (size == 0)
		return (s);
	while ((*src != '\0') && size > (c + 1))
	{
		*dest = *src;
		src++;
		dest++;
		c++;
	}
	if (size > 0)
		*dest = '\0';
	return (s);
}
