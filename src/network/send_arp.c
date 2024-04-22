/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_arp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:57:45 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/22 14:29:11 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

struct sockaddr_ll	*set_device(char *interface, t_cli_args *info) {
	struct sockaddr_ll	*device = ft_calloc(1, sizeof(struct sockaddr_ll));

	if ((device->sll_ifindex = if_nametoindex(interface)) == 0) {
		perror("if_nametoindex() failed to obtain interface index ");
		exit(EXIT_FAILURE);
	}

	device->sll_family = AF_PACKET;
	memcpy(device->sll_addr, info->source_mac, 6 * sizeof(uint8_t));
	device->sll_halen = 6;

	return (device);
}

void	set_arp_response(t_arp_hdr *arp_request, t_arp_packet *arp_response, t_cli_args *info) {
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
}

int	send_arp_request(t_arp_hdr *arp_request, char *interface, t_cli_args *info) {
	int					sd;
	t_arp_packet		*arp_response;
	struct sockaddr_ll	*device;
	
	device = set_device(interface, info);
	set_arp_response(arp_request, arp_response, info);

	if ((sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
		perror("socket() failed ");
		exit(EXIT_FAILURE);
	}

	if (sendto(sd, arp_response, sizeof(t_arp_packet), 0, (struct sockaddr *)&device, sizeof(device)) < 0) {
		perror("sendto() failed");
		exit(EXIT_FAILURE);
	}
	print_response_info(info->target_ip, info->source_ip);
	close(sd);
}
