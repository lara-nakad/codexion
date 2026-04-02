/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:00:10 by lnakad            #+#    #+#             */
/*   Updated: 2026/03/24 13:00:10 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	checking(char *s)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	while (is_space(s[i]))
		i++;
	if (s[i] == '-')
		error_printing("Should all be positive values");
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		if (num > (INT_MAX - (s[i] - '0')) / 10)
			error_printing("The value is too big, INT_MAX is the limit");
		num = num * 10 + (s[i] - '0');
		i++;
	}
	return (1);
}

void	parse_inputs(t_table *table, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc - 1)
	{
		if (checking(argv[i]) == -1)
			error_printing("Should be all positive and digits");
		i++;
	}
	table->nb_coders = atoi(argv[1]);
	table->time_to_burnout = atoi(argv[2]) * 1e3;
	table->time_to_compile = atoi(argv[3]) * 1e3;
	table->time_to_debug = atoi(argv[4]) * 1e3;
	table->time_to_refactor = atoi(argv[5]) * 1e3;
	table->nb_compiles_required = atoi(argv[6]);
	table->dongle_cooldown = atoi(argv[7]) * 1e3;
	if (strcmp(argv[8], "fifo") == 0)
		table->scheduler_flag = 0;
	else if (strcmp(argv[8], "edf") == 0)
		table->scheduler_flag = 1;
	else
		error_printing("Should be fifo or edf");
}
