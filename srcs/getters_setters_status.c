/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:32:04 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/17 18:38:31 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_state	get_status(t_philo *philo, t_state *value)
{
	t_state	status;

	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	status = *value;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	return (status);
}

void	set_status(t_philo *philo, t_state *dest, t_state status)
{
	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	if (philo->state != DEAD)
		*dest = status;
	else if (philo->state == DEAD)
		set_bool(&philo->table->table_mtx, &philo->table->end_simulation, true);
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
}
