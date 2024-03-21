/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 18:35:01 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/04 14:55:17 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	m;

	m = 0;
	while (m < n)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)(s));
		s++;
		m++;
	}
	return (NULL);
}
