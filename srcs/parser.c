/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:41:21 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/24 22:12:12 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	parser_data(int argc, char **argv)
{
	t_data	data;

	if (argc < 4 || argc > 5)
		return ;
	else
	{
		data.nb_philo = ft_atoi(argv[1]);
		data.time_to_die = ft_atoi(argv[2]);
		data.time_to_eat = ft_atoi(argv[3]);
		data.time_to_sleep = ft_atoi(argv[4]);
	}
	return (data);
}
