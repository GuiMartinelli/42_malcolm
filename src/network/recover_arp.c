/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_arp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:55:40 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 14:57:32 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

uint8_t *allocate_ustrmem(int len) {
	void *tmp;

	if (len <= 0) {
		fprintf(stderr, "ERROR: Cannot allocate memory because len = %i in allocate_ustrmem().\n", len);
		exit(EXIT_FAILURE);
	}

	tmp = (uint8_t *)malloc(len * sizeof(uint8_t));
	if (tmp != NULL) {
		memset(tmp, 0, len * sizeof(uint8_t));
		return (tmp);
	}

	else {
		fprintf(stderr, "ERROR: Cannot allocate memory for array allocate_ustrmem().\n");
		exit(EXIT_FAILURE);
	}
}

int	is_equal_address(uint8_t *ip_a, uint8_t *ip_b, int flag) {
	int i;

	i = 0;
	while (i < flag) {
		if (ip_a[i] != ip_b[i])
			return FALSE;
		i++;
	}
	return TRUE;
}

t_arp_hdr	*recover_arp_request(t_cli_args *info) {
	int			sd;
	uint8_t		*ether_frame;
	t_arp_hdr	*arp_request;

	ether_frame = allocate_ustrmem(IP_MAXPACKET);

	sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (sd < 0) {
		printf("Error getting socket descriptor\n");
		exit(1);
	}

	arp_request = (t_arp_hdr *) (ether_frame + 6 + 6 + 2);
	while (((((ether_frame[12]) << 8) + ether_frame[13]) != ETH_P_ARP) ||
		(ntohs(arp_request->opcode) != ARPOP_REPLY)) {

		if (recv(sd, ether_frame, IP_MAXPACKET, 0) < 0) {
			printf("recv() failed:");
			exit(EXIT_FAILURE);
		}

		if (is_equal_address(info->source_ip, arp_request->target_ip, IPv4) &&
			is_equal_address(info->target_ip, arp_request->sender_ip, IPv4) &&
			is_equal_address(info->target_mac, arp_request->sender_mac, MAC)) {
			printf("\nREQUEST RECOVERED SUCCESSFULLY!!!!\n\n");
			close(sd);
			return (arp_request);
		}
	}
	close(sd);
	return (NULL);
}