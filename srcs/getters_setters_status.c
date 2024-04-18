/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters_status.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 22:32:04 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/18 14:36:08 by agheredi         ###   ########.fr       */
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
	*dest = status;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
}
