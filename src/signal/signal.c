/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:25:31 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 14:41:14 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	terminate_program(int signal) {
	(void)signal;
	exit(1);
}

void	define_signal(void) {
	signal(SIGINT, terminate_program);
}
