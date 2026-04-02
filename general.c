/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 23:17:27 by lnakad            #+#    #+#             */
/*   Updated: 2026/03/30 23:17:27 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	gettime(t_time_code timeCode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_printing("Gettimeofday failed");
	if (timeCode == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (timeCode == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (timeCode == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_printing("Wrong input to gettime");
	return (-1);
}

int	error_printing(char *s)
{
	printf("%s\n", s);
	exit(-1);
}
