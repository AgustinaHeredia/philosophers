/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:03 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/11 13:09:20 by agheredi         ###   ########.fr       */
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
	i = -1;
	if (table->number_of_times_each_philo_must_eat == 0)
		return (1);
	if (table->number_of_philosophers == 1)
	{
		res = threads_error(pthread_create(&table->philo[0].thread_id,
					dinner_simulation, &table->philo[0], NULL), CREATE);
		if (res != 0)
			return (res);
	}
	else
	{
		while (++i < table->number_of_philosophers)
		{
			res = threads_error(pthread_create(&table->philo[i].thread_id,
						dinner_simulation, &table->philo[i], NULL), CREATE);
		}
	}
	return (res);
}
