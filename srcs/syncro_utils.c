/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:32:55 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/15 15:43:06 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, table->all_philo_ready))
		break ;
}

bool	simulation_finish(t_table *table)
{
	bool	finish;

	finish = false;
	if (table->end_simulation)
		finish = true;
	return (finish);
}

//si un filósofo no empieza a comer en time_to_die
//milisegundos desde el comienzo de su ultima comida o desde el principio de la
//simulación, este morirá.
bool	philo_died(t_philo *philo)
{
	bool	died;

	died = false;
	if (philo->table->end_simulation)
		died = true;
	return (died);
}
