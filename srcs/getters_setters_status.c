/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:32:04 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/16 23:56:30 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_state	get_status(t_philo *philo)
{
	t_state	status;

	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	status = philo->state;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	return (status);
}

void	set_status(t_philo *philo, t_state status)
{
	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	if (get_status(philo) != DEAD)
		philo->state = status;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
}
