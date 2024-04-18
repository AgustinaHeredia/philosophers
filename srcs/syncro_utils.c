/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:32:55 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/18 14:28:39 by agheredi         ###   ########.fr       */
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
	if (id_thread == philo_nbr || id_thread == -1)
	{
		res = true;
	}
	mtx_control(pthread_mutex_unlock(mutex), UNLOCK);
	return (res);
}

void	all_philo_full(t_table *table)
{
	int	i;
	int	count_full;

	i = -1;
	count_full = 0;
	mtx_control(pthread_mutex_lock(&table->table_mtx), LOCK);
	while (++i < table->nbr_of_philos)
	{
		if (get_status(&table->philo[i], &table->philo[i].state) == FULL)
			count_full++;
	}
	if (count_full == table->nbr_of_philos)
		set_bool(&table->table_mtx, &table->end_simulation, true);
	mtx_control(pthread_mutex_unlock(&table->table_mtx), UNLOCK);
}

bool	simulation_finish(t_table *table)
{
	bool	finish;
	int		i;

	i = -1;
	mtx_control(pthread_mutex_lock(&table->table_mtx), LOCK);
	while (++i < table->nbr_of_philos)
	{
		philo_died(&table->philo[i]);
	}
	mtx_control(pthread_mutex_unlock(&table->table_mtx), UNLOCK);
	all_philo_full(table);
	finish = get_bool(&table->table_mtx, &table->end_simulation);
	return (finish);
}

bool	philo_died(t_philo *philo)
{
	bool	died;
	long	time;

	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	died = false;
	time = time_elapsed(philo->table, get_time());
	if (philo->state == DEAD)
		died = true;
	else if (philo->table->time_to_die < philo->last_time_meal)
		died = true;
	else if (philo->table->time_to_die < time)
		died = true;
	else
		died = false;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	return (died);
}

	//printf("time died %ld, last %ld, elapse %ld\n", philo->table->time_to_die, philo->last_time_meal, time);
