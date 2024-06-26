/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:59:01 by guferrei          #+#    #+#             */
/*   Updated: 2024/06/04 15:59:55 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	clean_matrix(char **matrix) {
	if (matrix) {
		for (int i = 0; matrix[i]; i++)
			free_n_null(matrix[i]);
	}
	free_n_null(matrix);
}

int	count_addr_bytes(char **splitted_ip) {
	int	count;

	count = 0;
	while (*splitted_ip) {
		splitted_ip++;
		count++;
	}
	return (count);
}

void	set_delimiter(char *delimiter, int flag) {
	if (flag == IPv4)
		*delimiter = '.';
	else
		*delimiter = ':';
}

int	is_valid_addr(char *addr, int flag) {
	char	**splitted_addr;
	char	delimiter;

	if (!addr)
		return FALSE;

	set_delimiter(&delimiter, flag);
	splitted_addr = ft_split(addr, delimiter);

	if (count_addr_bytes(splitted_addr) != flag) {
		clean_matrix(splitted_addr);
		return FALSE;
	}

	for (int i = 0; i < flag; i++) {
		if (!is_valid_byte(splitted_addr[i], i, flag)) {
			clean_matrix(splitted_addr);
			return FALSE;
		}
	}
	clean_matrix(splitted_addr);
	return TRUE;
}

void cli_validator(int argc, char **argv) {
	if (argc != 5)
		program_error(ARGUMENTS_ERROR);
	
	if (is_valid_addr(argv[1], IPv4) &&
		is_valid_addr(argv[2], MAC) &&
		is_valid_addr(argv[3], IPv4) &&
		is_valid_addr(argv[4], MAC)) {
		return;
	}

	program_error(INPUT_ERROR);
}
