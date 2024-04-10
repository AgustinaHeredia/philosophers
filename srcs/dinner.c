/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:03 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/10 15:34:47 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	dinner_simulation()
{
}

int	dinner_star(t_table *table)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	// limits meals == 0
	//	return (res);
	if (table->number_of_philosophers == 1)
	{
		res = threads_error(pthread_create(&table->philo->thread_id, dinner_simutation, NULL), CREATE);
		if (res != 0)
			return (res);
	}
	else
	{
		while (i < table->number_of_philosophers)
		{
			i++;
		}
	}
	return (res);
}
