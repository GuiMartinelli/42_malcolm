/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guferrei <guferrei@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:59:01 by guferrei          #+#    #+#             */
/*   Updated: 2024/04/02 15:01:07 by guferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_malcolm.h"

int cli_validator(int argc, char **argv) {
	if (argc != 5)
		return (FALSE);
	
	// validate_ip(argv[1]);
	// validate_mac(argv[2]);
	// validate_ip(argv[3]);
	// validate_mac(argv[4]);

	return (TRUE);
}