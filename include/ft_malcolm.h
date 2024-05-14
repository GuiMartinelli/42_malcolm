/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 14:51:55 by guferrei          #+#    #+#             */
/*   Updated: 2024/05/14 14:58:42 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ifaddrs.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <bits/sigaction.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <bits/ioctls.h>
#include "../src/libft/libft.h"

#define TRUE 1
#define FALSE 0
#define IPv4 4 //Ipv4 lenght
#define MAC 6 //Mac lenght
#define ETH_HDRLEN 14	// Ethernet header length
#define IP4_HDRLEN 20	// IPv4 header length
#define ARP_HDRLEN 28	// ARP header length

typedef struct s_info {
	uint8_t	*target_ip;
	uint8_t	*target_mac;
	uint8_t	*source_ip;
	uint8_t	*source_mac;
	uint8_t	*ether_frame;
} t_info;

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

//Input Handling and Validation
t_info		*get_cli_args(char **argv);
int			cli_validator(int argc, char **argv);
int			is_valid_byte(char *byte, int index, int flag);

//Display
void		print_interface_info(char * interface);
void		print_error(char *msg);
void		print_ip(uint8_t *ip);
void		print_mac(uint8_t *mac);
void		print_request_info(uint8_t *target_ip, uint8_t *source_ip);
void		print_response_info(uint8_t *target_ip, uint8_t *source_ip);
void		print_exit(void);

//Signal
void		set_signal(void);

//Memory Cleaning
void		free_cli(t_info	*input);
void		free_n_null(void *ptr);

//Interface
char		*find_available_interface(void);

//Network
t_arp_hdr	*recover_arp_request(t_info *info);
int			send_arp_request(t_arp_hdr *arp_request, char *interface, t_info *info);

#endif