/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 00:03:30 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/05 01:02:55 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_lstsize(t_list *lst)
{
	int		c;
	t_list	*ptr;

	c = 0;
	ptr = lst;
	if (!lst)
		return (0);
	while (ptr != NULL)
	{
		ptr = ptr->next;
		c++;
	}
	return (c);
}
