/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:32:55 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/17 11:49:00 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mtx, &table->all_philo_ready))
		break ;
}

bool	all_thread_ready(t_mtx *mutex, int id_thread, int philo_nbr)
{
	bool	res;

	res = false;
	mtx_control(pthread_mutex_lock(mutex), LOCK);
	if (id_thread == philo_nbr)
	{
		res = true;
		printf("All threads are ready\n");
	}
	mtx_control(pthread_mutex_unlock(mutex), UNLOCK);
	return (res);
}

bool	simulation_finish(t_table *table)
{
	bool	finish;

	finish = get_bool(&table->table_mtx, &table->end_simulation);
	return (finish);
}

bool	philo_died(t_philo *philo)
{
	bool	died;

	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	died = false;
	if (philo->state == DEAD)
		died = true;
	else if (philo->table->time_to_die > philo->last_time_meal)
		died = true;
	else if (philo->table->time_to_die > time_elapsed(philo->table, get_time()))
		died = true;
	else
		died = false;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	if (died == true)
		set_bool(&philo->table->table_mtx, &philo->table->end_simulation, true);
	return (died);
}
