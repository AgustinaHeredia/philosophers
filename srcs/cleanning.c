/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:34:33 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/17 00:04:35 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->nbr_of_philos)
	{
		philo = table->philo + i;
		mtx_control(pthread_mutex_destroy(&philo->philo_mutex), DESTROY);
	}
	mtx_control(pthread_mutex_destroy(&table->table_mtx), DESTROY);
	free(table->fork);
	free(table->philo);
}
