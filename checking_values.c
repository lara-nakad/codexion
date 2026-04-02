/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnakad <lnakad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:22:36 by lnakad            #+#    #+#             */
/*   Updated: 2026/04/01 13:23:29 by lnakad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	check_coder_done(t_coder *coder)
{
	int	res;

	res = 0;
	pthread_mutex_lock(&coder->coder_mtx);
	if (coder->is_done)
		res = 1;
	pthread_mutex_unlock(&coder->coder_mtx);
	return (res);
}

int	check_value(pthread_mutex_t *t, int *val)
{
	int	v;

	pthread_mutex_lock(t);
	v = *val;
	pthread_mutex_unlock(t);
	return (v);
}

int	check_simulation_end(t_table *table)
{
	int	v;

	pthread_mutex_lock(&(table->table_mtx));
	v = table->end_simulation;
	pthread_mutex_unlock(&(table->table_mtx));
	return (v);
}
