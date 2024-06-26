/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:03 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/29 15:05:56 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)data;
	time = time_elapsed(philo->table, get_time());
	set_long(&philo->philo_mutex, &philo->last_time_meal, time);
	time = time_elapsed(philo->table, get_time());
	print_action(time, philo, "has taken a RIGHT fork", YEL);
	wait_time(get_long(&philo->table->table_mtx, &philo->table->time_to_die));
	return (NULL);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;
	long	time;

	table = data;
	while (!simulation_finish(table))
	{
		i = 0;
		while (i < table->nbr_of_philos && (!simulation_finish(table)))
		{
			if (philo_died(&table->philo[i]))
			{
				set_status(&table->philo[i], &table->philo[i].state, DEAD);
				mtx_control(pthread_mutex_lock(&table->table_mtx), LOCK);
				time = time_elapsed(table, get_time());
				printf("%s%ld %d %s%s\n", RED, time, (i + 1), "died", NC);
				table->end_simulation = true;
				mtx_control(pthread_mutex_unlock(&table->table_mtx), UNLOCK);
			}
			i++;
		}
	}
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_philo(philo->table);
	if (philo->id_philo % 2 == 0)
		wait_time(philo->table->time_to_eat * 0.5);
	while (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation)
			&& !(get_bool(&philo->philo_mutex, &philo->philo_full)))
			eat(philo);
		if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation)
			&& (get_status(philo, &philo->state) == EATING))
			ft_sleep(philo);
		if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation)
			&& (get_status(philo, &philo->state) == SLEEPING))
			thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_must_eat == 0)
		return ;
	else if (table->nbr_of_philos == 1)
		threads_control(pthread_create(&table->philo[0].thread_id, NULL,
				one_philo, &table->philo[0]), CREATE);
	else
	{
		while (++i < table->nbr_of_philos)
		{
			threads_control(pthread_create(&table->philo[i].thread_id, NULL,
					dinner_simulation, &table->philo[i]), CREATE);
		}
	}
	table->start_simulation = get_time();
	set_bool(&table->table_mtx, &table->all_philo_ready, true);
	monitor_dinner(table);
	table->nbr_thread = i;
	i = -1;
	while (++i < table->nbr_of_philos)
		threads_control(pthread_join(table->philo[i].thread_id, NULL), JOIN);
}
