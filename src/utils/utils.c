/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:09:49 by guferrei          #+#    #+#             */
/*   Updated: 2024/06/04 16:00:02 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	free_n_null(void *ptr) {
	if (ptr) {
		free(ptr);
		ptr = NULL;
	}
}

void	free_cli(t_info	*input) {
	free_n_null(input->source_ip);
	free_n_null(input->source_mac);
	free_n_null(input->target_ip);
	free_n_null(input->target_mac);
	free_n_null(input->ether_frame);
	free_n_null(input);
}

void	check_privileges() {
	if (geteuid() == 0)
		return;
	program_error(PRIVILEGES_ERROR);
}