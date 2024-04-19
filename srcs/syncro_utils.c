/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:32:55 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/19 15:38:05 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

//no lo est'a haciendo
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
		table->end_simulation = true;
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
//cheachear condicion de muerte
bool	philo_died(t_philo *philo)
{
	bool	died;
	long	time;

	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	died = false;
	time = time_elapsed(philo->table, get_time()) - philo->last_time_meal;
	if (philo->state == DEAD)
		died = true;
	else if (philo->table->time_to_die < time)
		died = true;
	else
		died = false;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	return (died);
}
