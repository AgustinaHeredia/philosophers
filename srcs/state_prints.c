/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_prints.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 21:54:56 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/03 13:06:43 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*eating(t_data *data)
{
	printf("%d %d is eating", data->time_to_eat, data->nb_philo);
}
