/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:35:59 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/10 15:23:10 by agheredi         ###   ########.fr       */
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

typedef struct s_fork
{
	t_mtx	fork;
	int		id_fork;
}	t_fork;

typedef struct s_philo
{
	int			id_philo;
	int			count_meals;
	bool		full;
	int			last_time_meal;
	t_fork		*left_fork;
	t_fork		*right_fork;
	pthread_t	thread_id;
	t_mtx		philo_mutex;
	t_table		*table;
}		t_philo;

struct s_table
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		number_of_times_each_philo_must_eat;
	int		start_simulation;
	bool	end_simulation;
	t_fork	*fork;
	t_philo	*philo;
};

//FUNCTIONS
//Functions parser
int			check_argv(char **argv);
void		parser_input(t_table *table, char **argv);

//Functions data init
int			data_init(t_table *table);
int			philo_init(t_table *table);
void		asigne_fork(t_philo *philo, t_fork *fork, int position);

//Functions Dinner
int			dinner_star(t_table *table);

//Functions utils
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
long long	ft_atol(const char *str);
int			check_char(char *argv);
size_t		ft_strlen(const char *s);

//Error function
int			ft_error(char *str);
int			mtx_error(int status, int mtx_code);
int			threads_error(int status, int code);

#endif
