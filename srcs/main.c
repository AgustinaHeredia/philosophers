/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:41:38 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/14 23:34:17 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		if (check_argv(argv) == 1)
			return (1);
		parser_input(&table, argv);
		if (data_init(&table) != 0)
			return (1);
		dinner_start(&table);
		clean(&table);
	}
	else
		return (ft_error("The number of arguments is not correct"));
	return (0);
}
