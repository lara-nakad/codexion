/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedular.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:44:50 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/01 22:09:21 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	release_dongle(t_dongle *d)
{
	pthread_mutex_lock(&(d->queue_protect));
	d->last_release_time = gettime(MILLISECOND);
	pthread_mutex_unlock(&(d->queue_protect));
	dequeue(d);
	pthread_mutex_unlock(&(d->lock));
}

t_coder	*pick_fifo(t_dongle *d)
{
	if (!d->waiting_queue)
		return (NULL);
	return (d->waiting_queue->coder);
}

t_coder	*pick_edf_safe(t_dongle *d)
{
	t_queue	*tmp;
	t_coder	*best;

	tmp = d->waiting_queue;
	if (!tmp)
		return (NULL);
	best = tmp->coder;
	while (tmp)
	{
		if (get_last_compile_time(tmp->coder)
			< get_last_compile_time(best))
			best = tmp->coder;
		tmp = tmp->next;
	}
	return (best);
}

void	request_dongle(t_dongle *d, t_coder *coder)
{
	long	now;
	t_coder	*best;
	long	last_release;	

	enqueue(d, coder);
	while (1)
	{
		pthread_mutex_lock(&(d->queue_protect));
		if (coder->table->scheduler_flag == 0)
			best = pick_fifo(d);
		else
			best = pick_edf_safe(d);
		last_release = d->last_release_time;
		pthread_mutex_unlock(&(d->queue_protect));
		if (best == coder)
		{
			now = gettime(MILLISECOND);
			if (now - last_release >= (coder->table->dongle_cooldown / 1e3))
				return ;
		}
		usleep(100);
	}
}
