/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:31 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/02 17:44:23 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	void	increment_running_threads(t_coder *coder)
{
	pthread_mutex_lock(&(coder->table->table_mtx));
	coder->table->nb_running_threads++;
	pthread_mutex_unlock(&(coder->table->table_mtx));
}

void	*coder_behavior(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	wait_all_threads(coder->table);
	increment_running_threads(coder)
	;
	while (!check_simulation_end(coder->table))
	{
		if (check_coder_done(coder))
			return (NULL);
		compile_routine(coder);
		debugging(coder);
		refactoring(coder);
	}
	return (NULL);
}

static	int	check_valid_table(t_table *table)
{
	if (table->nb_compiles_required == 0)
		return (0);
	if (table->nb_coders == 0)
		return (0);
	if (table->nb_coders == 1)
	{
		printf("Single coder needs 2 dongles in order to compile\n");
		return (0);
	}
	return (1);
}

static	void	set_compile_initially(t_table *table)
{
	int		i;
	t_coder	*coder;

	i = 0;
	while (i < table->nb_coders)
	{
		coder = &table->coders[i];
		pthread_mutex_lock(&coder->coder_mtx);
		coder->last_compile_time = gettime(MILLISECOND);
		pthread_mutex_unlock(&coder->coder_mtx);
		i++;
	}
}

void	simulation_start(t_table *table)
{
	int		i;
	t_coder	*coder;

	i = 0;
	if (!check_valid_table(table))
		return ;
	while (i < table->nb_coders)
	{
		coder = &table->coders[i];
		pthread_create(&coder->thread, NULL, coder_behavior, coder);
		i++;
	}
	pthread_create(&(table->monitor_thread), NULL, monitoring, table);
	table->start_simulation = gettime(MILLISECOND);
	set_compile_initially(table);
	pthread_mutex_lock(&(table->table_mtx));
	table->all_threads_ready = 1;
	pthread_mutex_unlock(&(table->table_mtx));
	i = 0;
	while (i < table->nb_coders)
	{
		pthread_join(table->coders[i].thread, NULL);
		i++;
	}
	pthread_join(table->monitor_thread, NULL);
}
