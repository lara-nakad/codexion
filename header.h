/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:22:52 by marvin            #+#    #+#             */
/*   Updated: 2026/03/19 13:22:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>

typedef struct s_dongle	t_dongle;
typedef struct s_table	t_table;

typedef struct s_queue
{
	struct s_coder	*coder;
	struct s_queue	*next;
}	t_queue;

typedef struct s_coder
{
	int				id;
	int				is_done;
	int				compile_count; //set first to zero
	long			last_compile_time; //for burnout
	pthread_t		thread;
	t_dongle		*first_dongle;
	t_dongle		*second_dongle;
	t_table			*table;
	pthread_mutex_t	coder_mtx;
}	t_coder;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	lock;
	long			last_release_time;
	t_queue			*waiting_queue;
	pthread_mutex_t	queue_protect;
	pthread_mutex_t	updating_time;
}	t_dongle;

typedef struct s_table
{
	int				nb_coders;
	long			time_to_compile;
	long			time_to_burnout;
	long			time_to_debug;
	long			time_to_refactor;
	int				nb_compiles_required;
	long			dongle_cooldown;
	long			start_simulation;
	int				all_threads_running;
	int				nb_running_threads;
	int				end_simulation;
	t_dongle		*dongles;
	t_coder			*coders;
	int				all_threads_ready;
	int				scheduler_flag;
	pthread_mutex_t	table_mtx;
	pthread_mutex_t	writing_mtx;
	pthread_t		monitor_thread;
}	t_table;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum s_coder_status
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
	TAKES_FIRST_DONGLE,
	TAKES_SECOND_DONGLE,
	BURNOUT,
}	t_coder_status;

int		error_printing(char *s);
void	parse_inputs(t_table *table, int argc, char **argv);
void	data_init(t_table *table);
void	wait_all_threads(t_table *table);
long	gettime(t_time_code timeCode);
int		check_simulation_end(t_table *table);
void	simulation_start(t_table *table);
void	printing_logs(t_coder *coder, t_coder_status status);
void	set_compile_time(t_coder *coder);
void	*monitoring(void *arg);
int		check_value(pthread_mutex_t *t, int *val);
void	enqueue(t_dongle *dongle, t_coder *coder);
void	dequeue(t_dongle *dongle);
void	request_dongle(t_dongle *dongle, t_coder *coder);
void	release_dongle(t_dongle *d);
void	debugging(t_coder *coder);
void	refactoring(t_coder *coder);
int		check_coder_done(t_coder *coder);
long	get_last_compile_time(t_coder *coder);
void	request_dongle(t_dongle *d, t_coder *coder);
void	cleanup(t_table *table);
void	compile_routine(t_coder *coder);