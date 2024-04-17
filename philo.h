/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:35:59 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/17 16:11:32 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>
# include <errno.h>

# define NC		"\e[0m"
# define YEL	"\e[93m"
# define LIL	"\e[95m"
# define RED	"\e[91m"
# define GRE	"\e[92m"
# define BLU	"\e[94m"
# define M      "\033[1;35m"
# define C      "\033[1;36m"

# define INIT 1
# define LOCK 2
# define UNLOCK 3
# define DESTROY 4
# define CREATE	5
# define DETACH 6
# define JOIN 7

# define MSN_ENOMEM "The process cannot allocate enough \
	memory to create another mutex."
# define MSN_EDEADLK "A deadlock would occur if \
	the thread blocked waiting for mutex."
# define MSN_EINVAL "The implementation has detected that the value specified by thread \
    does not refer to a joinable thread."
# define MSN_EPERM "The caller does not have appropriate permission to set \
    the required scheduling parameters or scheduling policy."
# define MSN_EAGAIN "The system lacked the necessary resources to create another thread, \
	or the system-imposed limit on the total number of threads in a process \
	[PTHREAD_THREADS_MAX] would be exceeded."
# define MSN_ESRCH " No thread could be found corresponding to that specified \
	by the given thread ID, thread."
# define MSN_EDEADLK_T "A deadlock was detected or the value of thread \
	specifies the calling thread."

//Structs
typedef struct s_table		t_table;
typedef pthread_mutex_t		t_mtx;

typedef enum e_philo_state
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5
}	t_state;

typedef struct s_fork
{
	t_mtx	fork;
	int		id_fork;
}	t_fork;

typedef struct s_philo
{
	int			id_philo;
	int			count_meals;
	long		last_time_meal;
	t_state		state;
	t_fork		*rigth_fork;
	t_fork		*left_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}		t_philo;

struct s_table
{
	int			nbr_of_philos;
	int			nbr_thread;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	int			nbr_must_eat;
	long		start_simulation;
	bool		all_philo_ready;
	bool		end_simulation;
	t_mtx		table_mtx;
	t_fork		*fork;
	t_philo		*philo;
	pthread_t	monitor;
};

//FUNCTIONS
//Functions parser
int			check_argv(char **argv);
void		parser_input(t_table *table, char **argv);

//Functions data init
int			data_init(t_table *table);
int			table_init(t_table *table);
int			philo_init(t_table *table);
void		asigne_fork(t_philo *philo, t_fork *fork, int position);

//Functions Dinner
void		dinner_start(t_table *table);
void		*dinner_simulation(void *data);
void		*monitor_dinner(void *data);
void		wait_all_threads(t_table *table);
bool		all_thread_ready(t_mtx *mutex, int id_thread, int philo_nbr);
void		*one_philo(void *data);

//actions dinner
void		eat(t_philo *philo);
void		take_fork(t_philo *philo);
void		drop_fork(t_fork *fork_right, t_fork *fork_left);
void		thinking(t_philo *philo);
void		ft_sleep(t_philo *philo);

//Functions utils
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
long long	ft_atol(const char *str);
int			check_char(char *argv);
size_t		ft_strlen(const char *s);
long		get_time(void);
long		time_elapsed(t_table *table, long actual_time);
void		wait_time(t_philo *philo, t_state state);
void		print_action(long time, t_philo *philo, char *str, char *color);
bool		simulation_finish(t_table *table);
bool		philo_died(t_philo *philo);
void		all_philo_full(t_table *table);

//Error function
int			ft_error(char *str);
int			mtx_control(int status, int mtx_code);
int			threads_control(int status, int code);

//getters and setters
void		set_bool(t_mtx *mutex, bool *dest, bool value);
bool		get_bool(t_mtx *mutex, bool *value);
void		set_long(t_mtx *mutex, long *dest, long value);
long		get_long(t_mtx *mutex, long *value);
t_state		get_status(t_philo *philo, t_state *value);
void		set_status(t_philo *philo, t_state *dest, t_state status);

//cleanning
void		clean(t_table *table);

#endif
