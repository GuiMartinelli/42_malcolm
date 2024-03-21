/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 08:00:25 by guferrei          #+#    #+#             */
/*   Updated: 2021/07/14 08:00:43 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putuns_fd(unsigned int n, int fd)
{
	char			str[11];
	char			*ptr;
	int				c;

	c = 0;
	ptr = &str[0];
	while (n > 9)
	{
		*(ptr + c) = (n % 10) + 48;
		n = n / 10;
		c++;
	}
	*(ptr + c) = n + 48;
	while (c >= 0)
	{
		write(fd, &*(ptr + c), 1);
		c--;
	}
}
