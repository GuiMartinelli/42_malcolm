/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:25:31 by guferrei          #+#    #+#             */
/*   Updated: 2024/06/04 16:22:06 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	terminate_program(int signal) {
	(void)signal;
	printf("\nClosing Program: ft_malcolm did not recovered any request\n");
	exit(1);
}

void	set_signal(void) {
	struct sigaction act = {0};

	act.sa_handler = &terminate_program;
	sigaction(SIGINT, &act, NULL);
}