/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:54:56 by agusheredia       #+#    #+#             */
/*   Updated: 2024/03/24 22:05:02 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	state_print(t_data *data)
{
	int	time;

	time = data->timestamp_in_ms;
	if ()
	{
		prinft("%d %d  has taken a fork\n", time, data->nb_philo);
	}
	else if ()
		prinft("%d %d   is eating\n", time, data->nb_philo);
	else if ()
		prinft("%d %d  is sleeping\n", time, data->nb_philo);
	else if ()
		prinft("%d %d   is thinking\n", time, data->nb_philo);
	else
		prinft("%d %d   died\n", time, data->nb_philo);
}
