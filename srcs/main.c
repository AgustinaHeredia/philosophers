/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 20:41:38 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/24 22:14:53 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	data = parser_data(argc, argv);
	if (!data)
	{
		printf("Number to argument is not valid\n");
		return (1);
	}
	//init struct
	//create threads
	//join threads
	//free struct
	return (0);
}
