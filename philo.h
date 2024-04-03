/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:35:59 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/03 13:06:55 by agheredi         ###   ########.fr       */
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

//Structs
typedef struct s_philo
{
}		t_philo;

typedef struct s_data
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
	int		timestamp_in_ms;
}		t_data;

//Parser functions
t_data	parser_data(char **argv);
void	create_threads(t_data *data);

//Threads functions
void	create_threads(t_data *data);

//state functions
void	*eating(t_data *data);

//Utils functions
int		ft_atoi(const char *str);
void	ft_error(char *str);

#endif
