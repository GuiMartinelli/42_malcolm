/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 20:46:48 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/04 19:21:21 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include"libft.h"

int	number_size(unsigned int n)
{
	int	c;

	c = 0;
	while (n > 9)
	{
		n = n / 10;
		c++;
	}
	c++;
	return (c);
}

void	nb_str(unsigned int nb, char *ptr, int c)
{
	while (nb > 9)
	{
		*(ptr + (c - 2)) = (nb % 10) + 48;
		nb = nb / 10;
		c--;
	}
	*(ptr + (c - 2)) = nb + 48;
}

char	*ft_itoa(int n)
{
	char			*ptr;
	unsigned int	nb;
	size_t			c;

	if (n < 0)
	{
		nb = n * -1;
		c = number_size(nb) + 2;
		ptr = ft_calloc(c, sizeof(char));
		if (!ptr)
			return (NULL);
		*ptr = '-';
	}
	else
	{
		nb = n;
		c = number_size(nb) + 1;
		ptr = ft_calloc(c, sizeof(char));
		if (!ptr)
			return (NULL);
	}
	nb_str(nb, ptr, c);
	return (ptr);
}
