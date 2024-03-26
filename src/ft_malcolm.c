/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:11:24 by guferrei          #+#    #+#             */
/*   Updated: 2024/03/26 15:30:02 by guferrei         ###   ########.fr       */
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

uint8_t	*set_ip(char *input) {
	uint8_t	*buf;
	int		status;

	buf = calloc(sizeof(struct in_addr), sizeof(struct in_addr));

	status = inet_pton(AF_INET, input, buf);

	if (status <= 0) {
		free(buf);
		return NULL;
	}

	return (buf);
}

int hex2num(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;
	return -1;
}

uint8_t	*set_mac(char *input) {
	uint8_t	*buf;
	int i;

	buf = calloc(7 * sizeof(uint8_t), 7 * sizeof(uint8_t));
	i = 0;

	while (i < 6) {
		int a;
		int b;

		a = hex2num(*input++);
		b = hex2num(*input++);

		if (a < 0 || b < 0 || (i < 5 && *input++ != ':'))
			return NULL;

		buf[i] = (a << 4) | b;
		i++;
	}

	return buf;
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

char *findAvailableInterface(void) {
	struct ifaddrs *ifaddr;
	char *if_name;
	char host[NI_MAXHOST];

	if_name = NULL;

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		exit(EXIT_FAILURE);
	}

	for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;

		if ((ifa->ifa_addr->sa_family == AF_INET ||
				ifa->ifa_addr->sa_family == AF_INET6) &&
				!ft_strncmp("eth", ifa->ifa_name, 3)) {
			if_name = ft_strdup(ifa->ifa_name);
			break;
		}
	}
	freeifaddrs(ifaddr);
	return(if_name);
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

struct arp_hdr	*recover_arp_request(struct cli_args *info) {
	int sd;
	uint8_t *ether_frame;
	struct arp_hdr *arp_request;

	ether_frame = allocate_ustrmem(IP_MAXPACKET);

	sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (sd < 0) {
		printf("Error getting socket descriptor\n");
		exit(1);
	}

	arp_request = (struct arp_hdr *) (ether_frame + 6 + 6 + 2);
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

int	sendArpRequest(struct arp_hdr *arp_request, char *interface, struct cli_args *info) {
	int	sd, frame_length;
	struct arp_packet *arp_response;
	struct sockaddr_in *ipv4;
	struct sockaddr_ll device;
	uint8_t *ether_frame;

	memset(&device, 0, sizeof(device));
	if ((device.sll_ifindex = if_nametoindex(interface)) == 0) {
		perror("if_nametoindex() failed to obtain interface index ");
		exit(EXIT_FAILURE);
	}

	device.sll_family = AF_PACKET;
	memcpy(device.sll_addr, info->source_mac, 6 * sizeof(uint8_t));
	device.sll_halen = 6;

	arp_response = ft_calloc(1, sizeof(struct arp_packet));

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

	if (sendto(sd, arp_response, sizeof(struct arp_packet), 0, (struct sockaddr *)&device, sizeof(device)) < 0) {
		perror("sendto() failed");
		exit(EXIT_FAILURE);
	}
	close(sd);
}

struct cli_args	*get_cli_args(char **argv) {
	struct cli_args	*input;

	input->source_ip = set_ip(argv[1]);
	input->source_mac = set_mac(argv[2]);
	input->target_ip = set_ip(argv[3]);
	input->target_mac = set_mac(argv[4]);

	if (!input->source_ip || !input->source_mac ||
			!input->target_ip || !input->target_mac) {
		perror("get_cli_args");
		exit(EXIT_FAILURE);
	}

	return input;
}

int main(int argc, char **argv) {
	struct arp_hdr	*arp_request;
	char 			*interface;
	struct cli_args	*input;


	if (!isValidInput(argc, argv)) {
		printf("INVALID INPUT\n");
		exit(1);
	}

	input = get_cli_args(argv);

	interface = findAvailableInterface();
	arp_request = recover_arp_request(input);
	sendArpRequest(arp_request, interface, input);
}