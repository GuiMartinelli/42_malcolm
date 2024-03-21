/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 22:18:30 by guferrei          #+#    #+#             */
/*   Updated: 2021/07/23 14:20:48 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *ptr)
{
	int			s;
	long int	n;

	s = 1;
	n = 0;
	while (*ptr == ' ' || *ptr == '\n'
		|| *ptr == '\t' || *ptr == '\v'
		|| *ptr == '\f' || *ptr == '\r')
	{
		ptr++;
	}
	if (*ptr == '-')
	{
		s = s * -1;
		ptr++;
	}
	else if (*ptr == '+')
		ptr++;
	while (*ptr >= 48 && *ptr <= 57)
	{
		n = n * 10;
		n = n + ((int)*ptr - 48);
		ptr++;
	}
	return (n * s);
}
