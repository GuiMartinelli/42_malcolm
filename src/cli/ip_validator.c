/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ip_validator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:41:33 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/25 15:42:09 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

int	count_ip_bytes(char **splitted_ip) {
	int	count;

	count = 0;
	while (*splitted_ip) {
		splitted_ip++;
		count++;
	}
	return (count);
}

int	is_valid_byte(char *byte, int index) {
	for(int i = 0; i < ft_strlen(byte); i++) {
		if (!ft_isdigit(byte[i]))
			return FALSE;
	}

	int decimal = ft_atoi(byte);

	if ((index == 0 && decimal > 0) ||
		(index == 3 && decimal < 255) ||
		((index > 0 && index < 3) && (decimal >= 0 && decimal <= 255)))
		return TRUE;
	return FALSE;
}

int	is_valid_ip(char *ip) {
	char	**splitted_ip;
	char	ip_byte;

	if (!ip)
		return FALSE;

	splitted_ip = ft_split(ip, '.');

	if (count_ip_bytes(splitted_ip) != 4)
		return FALSE;

	for (int i = 0; i < 4; i++) {
		if (!is_valid_byte(splitted_ip[i], i))
			return FALSE;
	}
	return TRUE;
}
