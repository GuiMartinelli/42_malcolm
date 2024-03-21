/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:21:33 by guferrei          #+#    #+#             */
/*   Updated: 2021/07/21 07:50:01 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		write (1, "(null)", 6);
	else
	{
		while (*s)
		{
			write(fd, &*s, 1);
			s++;
		}
	}
}
