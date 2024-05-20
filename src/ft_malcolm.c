/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:11:24 by guferrei          #+#    #+#             */
/*   Updated: 2024/05/20 15:46:07 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malcolm.h"

int	main(int argc, char **argv) {
	t_arp_hdr	*arp_request;
	char		*interface;
	t_info		*input;

	check_privileges();
	cli_validator(argc, argv);
	set_signal();

	input = get_cli_args(argv);
	interface = find_available_interface();
	if (!interface)
		print_error("Could not find interfaces");

	arp_request = recover_arp_request(input);
	if (!arp_request) {
		free_n_null(interface);
		free_cli(input);
		exit(1);
	}
	send_arp_request(arp_request, interface, input);
	free_n_null(interface);
	free_cli(input);
	printf("Exiting program...\n");
}
