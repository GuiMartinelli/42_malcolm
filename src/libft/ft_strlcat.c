/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 19:34:22 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/03 22:00:39 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	d;
	size_t	s;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	n = d;
	if (size <= d)
		return (size + s);
	else
	{
		dst = (dst + d);
		while ((size - 1) > n && *src != '\0')
		{
			*dst = *src;
			n++;
			dst++;
			src++;
		}
		*dst = '\0';
		return (d + s);
	}
}
