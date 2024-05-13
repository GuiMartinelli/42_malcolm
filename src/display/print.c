/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 15:00:22 by guferrei          #+#    #+#             */
/*   Updated: 2024/05/13 15:22:15 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

void	print_interface_info(char * interface) {
	if (interface)
		printf("Found available interface: %s\n", interface);
}

void	print_cli_error() {
	printf("Error: Invalid input!\n");
	exit(1);
}

void	print_interface_error() {
	printf("Error: Could not find interfaces\n");
	exit(1);
}

void	print_ip(uint8_t *ip) {
	printf ("%u.%u.%u.%u",
			ip[0],
			ip[1],
			ip[2],
			ip[3]);
}

void	print_mac(uint8_t *mac) {
	for (int i=0; i<6; i++) {
			printf ("%02x", mac[i]);
			if (i < 5)
				printf(":");
		}
}

void	print_request_info(uint8_t *target_ip, uint8_t *source_ip) {
	printf("ARP Request intercepted succesfully from Target ");
	print_ip(target_ip);
	printf(" to ");
	print_ip(source_ip);
	printf("\n");
}

void	print_response_info(uint8_t *target_ip, uint8_t *source_ip) {
	printf("ARP Response sended succesfully to Target ");
	print_ip(target_ip);
	printf(" spoofing MAC Address of ");
	print_ip(source_ip);
	printf("\n");
}

void	print_exit(void) {
	printf("\nClosing Program: ft_malcolm did not recovered any request\n");
}
