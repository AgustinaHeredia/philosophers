/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:01:28 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/10 15:15:31 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	mtx_error(int status, int mtx_code)
{
	int	res;

	res = 0;
	if (status == 0)
		return (res);
	else if (status == EINVAL && mtx_code == INIT)
		return (ft_error("The value specified by attr is invalid."));
	else if (status == EINVAL && (mtx_code == DESTROY
			|| mtx_code == LOCK || mtx_code == UNLOCK))
		return (ft_error("The value specified by mutex is invalid."));
	else if (status == ENOMEM)
		return (ft_error(MSN_ENOMEM));
	else if (status == EPERM)
		return (ft_error("The current thread does not hold a lock on mutex."));
	else if (status == EBUSY)
		return (ft_error("Mutex is locked."));
	else if (status == EDEADLK)
		return (ft_error(MSN_EDEADLK));
	return (res);
}

int	threads_error(int status, int code)
{
	int	res;

	res = 0;
	if (status == 0)
		return (res);
	else if (status == EINVAL && code == CREATE)
		return (ft_error("The value specified by attr is invalid."));
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		return (ft_error(MSN_EINVAL));
	else if (status == EPERM)
		return (ft_error(MSN_EPERM));
	else if (status == EAGAIN)
		return (ft_error(MSN_EAGAIN));
	else if (status == ESRCH)
		return (ft_error(MSN_ESRCH));
	else if (status == EDEADLK)
		return (ft_error(MSN_EDEADLK_T));
	return (res);
}
