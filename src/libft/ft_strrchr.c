/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 22:48:53 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/02 23:32:09 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int	cont;

	cont = 0;
	while (*(char *)s != '\0')
	{
		s++;
		cont++;
	}
	while (cont >= 0)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		else
		{
			s--;
			cont--;
		}
	}
	return (NULL);
}
