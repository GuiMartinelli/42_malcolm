/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:51:55 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 14:29:18 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
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
#include <bits/ioctls.h>
# include <signal.h>
#include "../src/libft/libft.h"

#define NI_MAXHOST 1025
#define NI_MAXSERV 32
#define TRUE 1
#define FALSE 0
#define IPv4 4
#define MAC 6
#define ETH_HDRLEN 14	// Ethernet header length
#define IP4_HDRLEN 20	// IPv4 header length
#define ARP_HDRLEN 28	// ARP header length

typedef struct s_cli_args {
	uint8_t	*target_ip;
	uint8_t	*target_mac;
	uint8_t	*source_ip;
	uint8_t	*source_mac;
} t_cli_args;

typedef struct s_ether_hdr {
	u_int8_t	dhost[MAC];
	u_int8_t	shost[MAC];
	u_int16_t	type;
} t_ether_hdr;

typedef struct s_arp_hdr {
	uint16_t	htype;
	uint16_t	ptype;
	uint8_t		hlen;
	uint8_t		plen;
	uint16_t	opcode;
	uint8_t		sender_mac[6];
	uint8_t		sender_ip[4];
	uint8_t		target_mac[6];
	uint8_t		target_ip[4];
} t_arp_hdr;

typedef struct s_arp_packet {
	t_ether_hdr	ether;
	t_arp_hdr	arp;
} t_arp_packet;

t_cli_args	*get_cli_args(char **argv);

void	define_signal(void);

char *findAvailableInterface(void);

#endif