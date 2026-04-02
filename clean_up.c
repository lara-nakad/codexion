/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 23:37:11 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/01 13:23:50 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	clear_queue(t_dongle *d)
{
	t_queue	*tmp;

	pthread_mutex_lock(&(d->queue_protect));
	while (d->waiting_queue)
	{
		tmp = d->waiting_queue;
		d->waiting_queue = d->waiting_queue->next;
		free(tmp);
	}
	pthread_mutex_unlock(&(d->queue_protect));
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_coders)
	{
		pthread_mutex_destroy(&table->coders[i].coder_mtx);
		i++;
	}
	i = 0;
	while (i < table->nb_coders)
	{
		clear_queue(&table->dongles[i]);
		pthread_mutex_destroy(&table->dongles[i].lock);
		pthread_mutex_destroy(&table->dongles[i].queue_protect);
		pthread_mutex_destroy(&table->dongles[i].updating_time);
		i++;
	}
	pthread_mutex_destroy(&table->table_mtx);
	pthread_mutex_destroy(&table->writing_mtx);
	free(table->coders);
	free(table->dongles);
}
