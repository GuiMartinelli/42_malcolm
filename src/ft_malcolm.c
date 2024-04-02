/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:11:24 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 14:42:15 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malcolm.h"

int isValidInput(int argc, char **argv) {
	if (argc != 5)
		return (FALSE);
	
	// validate_ip(argv[1]);
	// validate_mac(argv[2]);
	// validate_ip(argv[3]);
	// validate_mac(argv[4]);

	return (TRUE);
}

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

void	print_ip_n_mac(uint8_t *ip, uint8_t *mac) {
	if (ip) {
		printf ("IP: %u.%u.%u.%u\n",
			ip[0],
			ip[1],
			ip[2],
			ip[3]);
	}

	if (mac) {
		printf ("MAC: ");
		for (int i=0; i<6; i++) {
			printf ("%02x:", mac[i]);
		}
		printf("\n");
	}
}

int	sendArpRequest(t_arp_hdr *arp_request, char *interface, t_cli_args *info) {
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

int main(int argc, char **argv) {
	t_arp_hdr	*arp_request;
	char 		*interface;
	t_cli_args	*input;

	define_signal();

	if (!isValidInput(argc, argv)) {
		printf("INVALID INPUT\n");
		exit(1);
	}

	input = get_cli_args(argv);

	interface = findAvailableInterface();
	arp_request = recover_arp_request(input);
	sendArpRequest(arp_request, interface, input);
}