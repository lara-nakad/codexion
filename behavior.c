/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavior.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 22:53:15 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/02 17:58:23 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	compile_routine(t_coder *coder)
{
	request_dongle(coder->first_dongle, coder);
	pthread_mutex_lock(&(coder->first_dongle->lock));
	printing_logs(coder, TAKES_FIRST_DONGLE);
	request_dongle(coder->second_dongle, coder);
	pthread_mutex_lock(&(coder->second_dongle->lock));
	printing_logs(coder, TAKES_SECOND_DONGLE);
	set_compile_time(coder);
	pthread_mutex_lock(&coder->coder_mtx);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->coder_mtx);
	usleep(coder->table->time_to_compile);
	printing_logs(coder, COMPILING);
	pthread_mutex_lock(&coder->coder_mtx);
	if (coder->compile_count == coder->table->nb_compiles_required)
		coder->is_done = 1;
	pthread_mutex_unlock(&coder->coder_mtx);
	release_dongle(coder->first_dongle);
	release_dongle(coder->second_dongle);
}

void	debugging(t_coder *coder)
{
	printing_logs(coder, DEBUGGING);
	usleep(coder->table->time_to_debug);
}

void	refactoring(t_coder *coder)
{
	printing_logs(coder, REFACTORING);
	usleep(coder->table->time_to_refactor);
}
