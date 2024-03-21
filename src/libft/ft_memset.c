/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 19:16:11 by guferrei          #+#    #+#             */
/*   Updated: 2021/05/28 19:17:16 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>

void	*ft_memset(void *ptr, int c, size_t n)
{
	int	cont;

	cont = 0;
	while (cont < (int)n)
	{
		*(unsigned char *)(ptr + cont) = c;
		cont++;
	}
	return (ptr);
}
