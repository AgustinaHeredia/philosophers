/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:41:38 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/03 12:59:58 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 6 || argv[3] == NULL)
	{
		printf("Number to argument is not valid\n");
		return (1);
	}
	data = parser_data(argv);
	create_threads(&data);
	//join threads
	//free struct
	return (0);
}
