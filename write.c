/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:46:29 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/01 22:23:19 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	printing_logs(t_coder *coder, t_coder_status status)
{
	long	time;

	pthread_mutex_lock(&(coder->table->writing_mtx));
	time = gettime(MILLISECOND) - coder->table->start_simulation;
	if (status == BURNOUT)
		printf("%-6ld %d burned out\n", time, coder->id);
	else if (!check_simulation_end(coder->table) || check_coder_done(coder))
	{
		if (status == COMPILING)
			printf("%-6ld %d is compiling\n", time, coder->id);
		else if (status == TAKES_FIRST_DONGLE || status == TAKES_SECOND_DONGLE)
			printf("%-6ld %d has taken a dongle\n", time, coder->id);
		else if (status == DEBUGGING)
			printf("%-6ld %d is debugging\n", time, coder->id);
		else if (status == REFACTORING)
			printf("%-6ld %d is refactoring\n", time, coder->id);
	}
	pthread_mutex_unlock(&(coder->table->writing_mtx));
}
