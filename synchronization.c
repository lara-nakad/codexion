/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchronization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:32:45 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/01 13:23:08 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	wait_all_threads(t_table *table)
{
	while (!(check_value(&table->table_mtx, &(table->all_threads_ready))))
		;
}

void	set_compile_time(t_coder *coder)
{
	pthread_mutex_lock(&coder->coder_mtx);
	coder->last_compile_time = gettime(MILLISECOND);
	pthread_mutex_unlock(&coder->coder_mtx);
}

long	get_last_compile_time(t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&coder->coder_mtx);
	time = coder->last_compile_time;
	pthread_mutex_unlock(&coder->coder_mtx);
	return (time);
}
