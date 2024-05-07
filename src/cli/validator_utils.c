/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:41:33 by guferrei          #+#    #+#             */
/*   Updated: 2024/05/07 15:45:39 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

int	is_hex(int c) {
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c <= 102))
		return (1);
	else
		return (0);
}

int	is_valid_mac_byte(char *byte) {
	for(size_t i = 0; i < ft_strlen(byte); i++) {
		if (!is_hex(byte[i]))
			return FALSE;
	}

	if (ft_strlen(byte) != 2)
		return FALSE;

	return TRUE;
}

int	is_valid_ip_byte(char *byte, int index) {
	for(size_t i = 0; i < ft_strlen(byte); i++) {
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

int	is_valid_byte(char *byte, int index, int flag) {
	return (flag == IPv4 ?
				is_valid_ip_byte(byte, index) : is_valid_mac_byte(byte));
}
