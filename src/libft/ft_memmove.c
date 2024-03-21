/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 22:40:07 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/04 19:38:11 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	c;

	c = 0;
	if (!dest && !src)
		return (NULL);
	if (dest > src)
	{
		while (n > 0)
		{
			*(char *)(dest + (n - 1)) = *(char *)(src + (n - 1));
			n--;
		}
	}
	else
	{
		while (c < n)
		{
			*(char *)(dest + c) = *(char *)(src + c);
			c++;
		}
	}
	return (dest);
}
