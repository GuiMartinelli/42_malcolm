/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 15:20:08 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 15:09:52 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

char *find_available_interface(void) {
	struct ifaddrs *ifaddr;
	char *if_name;
	char host[NI_MAXHOST];

	if_name = NULL;

	if (getifaddrs(&ifaddr) == -1) {
		printf("Error: Could not find interfaces\n");
		return (NULL);
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

	print_interface_info(if_name);
	freeifaddrs(ifaddr);
	return(if_name);
}
