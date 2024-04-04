/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:35:59 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/04 16:46:09 by agheredi         ###   ########.fr       */
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

//Enum
enum	e_control_code
{
	INIT,
	DESTROY,
	LOCK,
	UNLOCK,
	JOIN,
	DETACH,
};

//Structs
typedef pthread_t		t_mtx;

typedef struct s_table	t_table;

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
	int		end_simulation;
	t_fork	*fork;
	t_philo	philo;
};

//FUNCTIONS
//Functions parser
int			check_argv(char **argv);
void		parser_input(t_table *table, char **argv);

//Functions data init
void		data_init(t_table *table);

//Functions utils
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
long long	ft_atol(const char *str);
int			check_char(char *argv);
size_t		ft_strlen(const char *s);

//Error function
int			ft_error(char *str);

#endif
