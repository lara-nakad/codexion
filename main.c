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
		if (parse_inputs(&table, argc, argv) == -1)
			return (-1);
		if (data_init(&table) == -1)
			return (-1);
		simulation_start(&table);
		cleanup(&table);
	}
	else
	{
		printf("Invalid number of arguments!\n");
		return (-1);
	}
}
