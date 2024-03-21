/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 08:14:18 by guferrei          #+#    #+#             */
/*   Updated: 2021/07/21 14:27:43 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	divide(unsigned long long nbr, int base)
{
	int	size;

	size = 1;
	while (nbr >= (unsigned long long)base)
	{
		nbr /= base;
		size++;
	}
	return (size);
}

int	ft_nbrlen(long long nbr, int base)
{
	int					size;
	unsigned long long	n;

	if (base == 10 && nbr < 0)
		n = nbr * -1;
	else
		n = nbr;
	size = divide(n, base);
	return (size);
}
