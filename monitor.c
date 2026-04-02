/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 17:11:20 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/01 14:14:30 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static	int	all_coders_done(t_table *table)
{
	int		i;
	int		done_count;
	t_coder	*coder;

	done_count = 0;
	i = 0;
	while (i < table->nb_coders)
	{
		coder = &table->coders[i];
		if (check_value(&(coder->coder_mtx), &(coder->is_done)))
			done_count++;
		i++;
	}
	return (done_count == table->nb_coders);
}

static	int	all_threads_running(t_table *table)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&(table->table_mtx));
	if (table->nb_coders == table->nb_running_threads)
		res = 1;
	pthread_mutex_unlock(&(table->table_mtx));
	return (res);
}

static	int	coder_died(t_coder *coder)
{
	long	last_compile;
	long	t_to_die;
	long	elapsed;

	if (check_value(&(coder->coder_mtx), &(coder->is_done)))
		return (0);
	last_compile = get_last_compile_time(coder);
	elapsed = gettime(MILLISECOND) - last_compile;
	t_to_die = coder->table->time_to_burnout;
	if (elapsed > (t_to_die / 1e3))
		return (1);
	return (0);
}

static	void	set_end_simulation(t_table *table)
{
	pthread_mutex_lock(&(table->table_mtx));
	table->end_simulation = 1;
	pthread_mutex_unlock(&(table->table_mtx));
}

void	*monitoring(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *)arg;
	while (!all_threads_running(table))
		;
	while (!check_simulation_end(table))
	{
		i = 0;
		while (i < table->nb_coders && !check_simulation_end(table))
		{
			if (coder_died(&(table->coders[i])))
			{
				set_end_simulation(table);
				printing_logs(&(table->coders[i]), BURNOUT);
			}
			if (all_coders_done(table))
				set_end_simulation(table);
			i++;
		}
	}
	return (NULL);
}
