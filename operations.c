/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:34:14 by lnakad            #+#    #+#             */
/*   Updated: 2026/03/31 22:36:00 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	enqueue(t_dongle *dongle, t_coder *coder)
{
	t_queue	*node;
	t_queue	*tmp;

	node = malloc(sizeof(t_queue));
	if (!node)
		return ;
	node->coder = coder;
	node->next = NULL;
	pthread_mutex_lock(&(dongle->queue_protect));
	if (!dongle->waiting_queue)
		dongle->waiting_queue = node;
	else
	{
		tmp = dongle->waiting_queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	pthread_mutex_unlock(&(dongle->queue_protect));
}

void	dequeue(t_dongle *dongle)
{
	t_queue	*tmp;

	pthread_mutex_lock(&(dongle->queue_protect));
	if (dongle->waiting_queue)
	{
		tmp = dongle->waiting_queue;
		dongle->waiting_queue = dongle->waiting_queue->next;
		free(tmp);
	}
	pthread_mutex_unlock(&(dongle->queue_protect));
}
