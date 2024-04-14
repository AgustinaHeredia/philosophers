/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 21:17:50 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/14 22:19:54 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_bool(t_mtx *mutex, bool *dest, bool value)
{
	mtx_error(pthread_mutex_lock(&mutex), LOCK);
	dest = value;
	mtx_error(pthread_mutex_unlock(&mutex), UNLOCK);
}

bool	get_bool(t_mtx *mutex, bool value)
{
	bool	rest;

	mtx_error(pthread_mutex_lock(&mutex), LOCK);
	rest = value;
	mtx_error(pthread_mutex_unlock(&mutex), UNLOCK);
	return (rest);
}

void	set_long(t_mtx *mutex, long *dest, long value)
{
	mtx_error(pthread_mutex_lock(&mutex), LOCK);
	dest = value;
	mtx_error(pthread_mutex_unlock(&mutex), UNLOCK);
}

long	get_long(t_mtx *mutex, long value)
{
	long	rest;

	mtx_error(pthread_mutex_lock(&mutex), LOCK);
	rest = value;
	mtx_error(pthread_mutex_unlock(&mutex), UNLOCK);
	return (rest);
}
