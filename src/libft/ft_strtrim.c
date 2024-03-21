/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 18:17:52 by guferrei          #+#    #+#             */
/*   Updated: 2021/06/04 17:39:52 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include<stdlib.h>

char const	*test_beg(char const *s1, char const *set)
{
	int	s;

	s = 0;
	while (*(set + s))
	{
		if (*s1 == '\0')
			return (s1);
		else if (*(set + s) == *s1)
		{
			s1++;
			s = 0;
		}
		else
			s++;
	}
	return (s1);
}

char const	*test_end(char const *ptr, char const *set)
{
	int	s;

	s = 0;
	while (*(set + s))
	{
		if (*(set + s) == *ptr)
		{
			ptr--;
			s = 0;
		}
		else
			s++;
	}
	return (ptr);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*ptr;
	const char	*str;
	size_t		c;
	int			s;

	s = 0;
	c = ft_strlen((char *)s1);
	ptr = (s1 + c) - 1;
	s1 = test_beg(s1, set);
	if (*s1 == '\0')
	{
		str = ft_calloc(1, sizeof(char));
		return ((char *)str);
	}
	ptr = test_end(ptr, set);
	str = ft_calloc((ptr - s1) + 3, sizeof(char));
	if (str == NULL)
		return (NULL);
	while (s1 <= ptr)
	{
		*(char *)(str + s) = *(char *)s1;
		s++;
		s1++;
	}
	return ((char *)str);
}
