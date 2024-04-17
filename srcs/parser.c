/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:41:21 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/16 17:14:07 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_argv(char **argv)
{
	int			i;
	long long	nbr;

	i = 1;
	while (argv[i])
	{
		if (check_char(argv[i]) == 1)
			return (ft_error("Only acept numeric argumnets"));
		if (ft_strlen(argv[i]) > 14)
			return (ft_error("Only argument it too long"));
		nbr = ft_atol(argv[i]);
		if (nbr > INT_MAX || nbr < 0)
			return (ft_error("No acept numbers negatives or INT MAX"));
		i++;
	}
	return (0);
}

void	parser_input(t_table *table, char **argv)
{
	table->nbr_of_philos = (int)ft_atol(argv[1]);
	table->time_to_die = (int)ft_atol(argv[2]);
	table->time_to_eat = (int)ft_atol(argv[3]);
	table->time_to_sleep = (int)ft_atol(argv[4]);
	if (argv[5])
		table->nbr_must_eat = (int)ft_atol(argv[5]);
	else
		table->nbr_must_eat = -1;
}
