/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:35:02 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/03 13:05:05 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_threads(t_data *data)
{
	pthread_t	th[data->nb_philo];
	int			i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&th[i], NULL, &eating, NULL) != 0)
			ft_error("Failed to create thread");
		i++;
	}
}
