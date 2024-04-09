/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:01:28 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/08 22:35:04 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	handle_mutex_error(int status, int mtx_code)
{
	int	res;

	res = 0;
	if (status == 0)
		return (res);
	else if (status == EINVAL && mtx_code == INIT)
		return (ft_error("The value specified by attr is invalid."));
	else if (status == EINVAL && (mtx_code == DESTROIT
			|| mtx_code == LOCK || mtx_code == UNLOCK))
		return (ft_error("The value specified by mutex is invalid."));
	else if (status == ENOMEM)
		return (ft_error("The process cannot allocate enough memory to create another mutex."));
	else if (status == EPERM)
		return (ft_error("The current thread does not hold a lock on mutex."));
	else if (status == EBUSY)
		return (ft_error("Mutex is locked."));
	else if (status == EDEADLK)
		return (ft_error("A deadlock would occur if the thread blocked waiting for mutex."));
	return (res);
}
