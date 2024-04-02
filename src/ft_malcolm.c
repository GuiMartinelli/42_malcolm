/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:11:24 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 15:17:56 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_malcolm.h"

int main(int argc, char **argv) {
	t_arp_hdr	*arp_request;
	char 		*interface;
	t_cli_args	*input;

	define_signal();

	if (!cli_validator(argc, argv))
		print_cli_error();

	input = get_cli_args(argv);

	interface = find_available_interface();
	if (!interface)
		print_interface_error();

	arp_request = recover_arp_request(input);
	send_arp_request(arp_request, interface, input);
}