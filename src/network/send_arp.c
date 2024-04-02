/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_arp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:57:45 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 15:02:29 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

int	send_arp_request(t_arp_hdr *arp_request, char *interface, t_cli_args *info) {
	int					sd;
	int					frame_length;
	t_arp_packet		*arp_response;
	struct sockaddr_in	*ipv4;
	struct sockaddr_ll	device;
	uint8_t				*ether_frame;

	memset(&device, 0, sizeof(device));
	if ((device.sll_ifindex = if_nametoindex(interface)) == 0) {
		perror("if_nametoindex() failed to obtain interface index ");
		exit(EXIT_FAILURE);
	}

	device.sll_family = AF_PACKET;
	memcpy(device.sll_addr, info->source_mac, 6 * sizeof(uint8_t));
	device.sll_halen = 6;

	arp_response = ft_calloc(1, sizeof(t_arp_packet));

	ft_memcpy(arp_response->ether.dhost, arp_request->sender_mac, 6 * sizeof(uint8_t));
	ft_memcpy(arp_response->ether.shost, info->source_mac, 6 * sizeof(uint8_t));
	arp_response->ether.type = htons(ETHERTYPE_ARP);

	arp_response->arp.htype = htons(ARPHRD_ETHER);
	arp_response->arp.ptype = htons(ETHERTYPE_IP);
	arp_response->arp.hlen = MAC;
	arp_response->arp.plen = IPv4;
	arp_response->arp.opcode = htons(ARPOP_REQUEST);
	ft_memcpy(arp_response->arp.sender_ip, arp_request->target_ip, 4 * sizeof(uint8_t));
	ft_memcpy(arp_response->arp.sender_mac, info->source_mac, 6 * sizeof(uint8_t));
	ft_memcpy(arp_response->arp.target_ip, arp_request->sender_ip, 4 * sizeof(uint8_t));

	if ((sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
		perror("socket() failed ");
		exit(EXIT_FAILURE);
	}

	if (sendto(sd, arp_response, sizeof(t_arp_packet), 0, (struct sockaddr *)&device, sizeof(device)) < 0) {
		perror("sendto() failed");
		exit(EXIT_FAILURE);
	}
	close(sd);
}
