/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:42:17 by guferrei          #+#    #+#             */
/*   Updated: 2021/05/28 19:22:34 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

unsigned int	signal(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = n * -1;
	}
	else
		nb = n;
	return (nb);
}

void	ft_putnbr_fd(int n, int fd)
{
	char			str[11];
	char			*ptr;
	int				c;
	unsigned int	nb;

	c = 0;
	ptr = &str[0];
	nb = signal(n, fd);
	while (nb > 9)
	{
		*(ptr + c) = (nb % 10) + 48;
		nb = nb / 10;
		c++;
	}
	*(ptr + c) = nb + 48;
	while (c >= 0)
	{
		write(fd, &*(ptr + c), 1);
		c--;
	}
}
