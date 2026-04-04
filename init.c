/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:44 by lnakad            #+#    #+#             */
/*   Updated: 2026/03/24 12:59:44 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	void	assign_dongles(t_coder *coder, int position, t_table *table)
{
	int	nb_coders;

	nb_coders = table->nb_coders;
	if (coder->id % 2 == 0)
	{
		coder->first_dongle = &table->dongles[position];
		coder->second_dongle = &table->dongles[(position + 1) % nb_coders];
	}
	else
	{
		coder->first_dongle = &table->dongles[(position + 1) % nb_coders];
		coder->second_dongle = &table->dongles[position];
	}
}

static	void	coders_init(t_table *table)
{
	int		i;
	t_coder	*coder;

	i = 0;
	while (i < table->nb_coders)
	{
		coder = &(table->coders[i]);
		coder->id = (i + 1);
		coder->is_done = 0;
		coder->compile_count = 0;
		coder->table = table;
		pthread_mutex_init(&coder->coder_mtx, NULL);
		assign_dongles(coder, i, table);
		i++;
	}
}

static	int	allocate_resources(t_table *table)
{
	table->coders = malloc(table->nb_coders * (sizeof(t_coder)));
	if (!table->coders)
	{
		printf("Allocation failed\n");
		return (-1);
	}
	table->dongles = malloc(table->nb_coders * (sizeof(t_dongle)));
	if (!table->dongles)
	{
		free(table->coders);
		printf("Allocation failed\n");
		return (-1);
	}
	return (1);
}

int	data_init(t_table *table)
{
	int	i;

	i = 0;
	table->end_simulation = 0;
	table->all_threads_ready = 0;
	table->all_threads_running = 0;
	table->nb_running_threads = 0;
	if (allocate_resources(table) == -1)
		return (-1);
	pthread_mutex_init(&(table->table_mtx), NULL);
	pthread_mutex_init(&(table->writing_mtx), NULL);
	while (i < table->nb_coders)
	{
		table->dongles[i].id = i;
		table->dongles[i].waiting_queue = NULL;
		table->dongles[i].last_release_time = 0;
		pthread_mutex_init(&(table->dongles[i].queue_protect), NULL);
		pthread_mutex_init(&(table->dongles[i].lock), NULL);
		pthread_mutex_init(&(table->dongles[i].updating_time), NULL);
		i++;
	}
	coders_init(table);
	return (1);
}
