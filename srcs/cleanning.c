/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:34:33 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/22 12:37:16 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->nbr_of_philos)
	{
		philo = &table->philo[i];
		mtx_control(pthread_mutex_destroy(&philo->philo_mutex), DESTROY);
		i++;
	}
	i = 0;
	while (i < table->nbr_of_philos)
	{
		mtx_control(pthread_mutex_destroy(&table->fork[i]), DESTROY);
		i++;
	}
	mtx_control(pthread_mutex_destroy(&table->table_mtx), DESTROY);
	mtx_control(pthread_mutex_destroy(&table->time_mtx), DESTROY);
	free(table->fork);
	free(table->philo);
}
