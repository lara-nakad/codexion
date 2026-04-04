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

static int	check_digit(char c)
{
	if (c < '0' || c > '9')
	{
		printf("Should pass numbers only!\n");
		return (0);
	}
	return (1);
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
	{
		printf("Should all be positive values!\n");
		return (-1);
	}
	while (s[i])
	{
		if (!check_digit(s[i]))
			return (-1);
		if (num > (INT_MAX - (s[i] - '0')) / 10)
		{
			printf("The value is too big, INT_MAX is the limit\n");
			return (-1);
		}
		num = num * 10 + (s[i] - '0');
		i++;
	}
	return (1);
}

static	int	parse_scheduler(char *arg)
{
	if (strcmp(arg, "fifo") == 0)
		return (0);
	else if (strcmp(arg, "edf") == 0)
		return (1);
	else
		return (-1);
}

int	parse_inputs(t_table *table, int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc - 1)
	{
		if (checking(argv[i]) == -1)
			return (-1);
		i++;
	}
	table->nb_coders = atoi(argv[1]);
	table->time_to_burnout = atoi(argv[2]) * 1e3;
	table->time_to_compile = atoi(argv[3]) * 1e3;
	table->time_to_debug = atoi(argv[4]) * 1e3;
	table->time_to_refactor = atoi(argv[5]) * 1e3;
	table->nb_compiles_required = atoi(argv[6]);
	table->dongle_cooldown = atoi(argv[7]) * 1e3;
	table->scheduler_flag = parse_scheduler(argv[8]);
	if (table->scheduler_flag == -1)
	{
		printf("flag should be fifo or edf\n");
		return (-1);
	}
	return (1);
}
