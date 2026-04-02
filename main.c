/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:01 by lnakad            #+#    #+#             */
/*   Updated: 2026/03/24 13:00:01 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 9)
	{
		parse_inputs(&table, argc, argv);
		data_init(&table);
		simulation_start(&table);
		cleanup(&table);
	}
	else
		error_printing("Invalid number of arguments!");
}
