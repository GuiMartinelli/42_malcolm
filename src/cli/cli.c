/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:11:43 by guferrei          #+#    #+#             */
/*   Updated: 2024/05/14 15:06:54 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

uint8_t	*set_ip(char *input) {
	uint8_t	*buf;
	int		status;

	buf = malloc(IPv4 * sizeof(uint8_t));

	status = inet_pton(AF_INET, input, buf);
	if (status <= 0) {
		free(buf);
		return (NULL);
	}

	return (buf);
}

int hex2num(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

uint8_t	*set_mac(char *input) {
	uint8_t	*buf;

	buf = malloc(MAC * sizeof(uint8_t));

	for (int i = 0; i < MAC; i++) {
		int a;
		int b;

		a = hex2num(*input++);
		b = hex2num(*input++);

		if (a < 0 || b < 0 || (i < 5 && *input++ != ':'))
			return NULL;

		buf[i] = (a << 4) | b;
	}

	return buf;
}

t_info	*get_cli_args(char **argv) {
	t_info	*input;

	input = malloc(sizeof(t_info));

	input->source_ip = set_ip(argv[1]);
	input->source_mac = set_mac(argv[2]);
	input->target_ip = set_ip(argv[3]);
	input->target_mac = set_mac(argv[4]);

	if (!input->source_ip || !input->source_mac ||
			!input->target_ip || !input->target_mac) {
		print_error("Input was not writed correctly");
		exit(1);
	}

	return (input);
}
