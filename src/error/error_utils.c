/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:57:22 by guferrei          #+#    #+#             */
/*   Updated: 2024/06/04 16:42:02 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	error_msg(char *msg) {
	printf("ERROR: %s\n\nExiting program...\n", msg);
}

void	interface_error() {
	error_msg("Interface not found");
	exit(1);
}

void	input_error() {
	error_msg("IP or MAC address is invalid");
	exit(1);
}

void	arguments_error() {
	printf("ERROR: Wrong number of arguments\n");
	printf("\tThe program must be executed with root privileges and with the following arguments:\n");
	printf("\tsudo ./ft_malcolm [SOURCE IP] [SOURCE MAC] [TARGET IP] [TARGET MAC]\n\n");
	printf("Exiting program...\n");
	exit(1);
}

void	socket_error() {
	error_msg("Unexpected socket() error");
	exit(1);
}

void	recv_error() {
	error_msg("Unexpected recv() error");
	exit(1);
}

void	privileges_error() {
	printf("ERROR: Root privileges are required to run the program\n");
	printf("\tThe program must be executed with root privileges and with the following arguments:\n");
	printf("\tsudo ./ft_malcolm [SOURCE IP] [SOURCE MAC] [TARGET IP] [TARGET MAC]\n\n");
	printf("Exiting program...\n");
	exit(1);
}

void	send_to_error() {
	error_msg("Unexpected sendto() error");
	exit(1);
}

