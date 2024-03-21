/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 19:47:31 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/04 19:38:06 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	c;

	c = 0;
	if (!dest && !src)
		return (NULL);
	while ((int)n > c)
	{
		*(unsigned char *)(dest + c) = *(unsigned char *)src;
		src++;
		c++;
	}
	return (dest);
}
