/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:53:25 by guferrei          #+#    #+#             */
/*   Updated: 2024/06/04 16:41:59 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	program_error(int code) {
	switch (code) {
	case INTERFACE_NOT_FOUND_ERROR:
		interface_error();
		break;
	case INPUT_ERROR:
		input_error();
		break;
	case ARGUMENTS_ERROR:
		arguments_error();
		break;
	case SOCKET_ERROR:
		socket_error();
		break;
	case RECV_ERROR:
		recv_error();
		break;
	case PRIVILEGES_ERROR:
		privileges_error();
		break;
	case SEND_TO_ERROR:
		send_to_error();
		break;
	}
}
