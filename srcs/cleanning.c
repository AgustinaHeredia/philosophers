/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 23:34:33 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/14 23:50:31 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->number_of_philosophers)
	{
		philo = table->philo + i;
		mtx_error(pthread_mutex_destroy(&philo->philo_mutex), DESTROY);
	}
	mtx_error(pthread_mutex_destroy(&table->table_mutex), DESTROY);
	free(table->fork);
	free(table->philo);
}
