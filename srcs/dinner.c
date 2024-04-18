/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:03 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/18 15:59:10 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	time = time_elapsed(philo->table, get_time());
	set_long(&philo->philo_mutex, &philo->last_time_meal, time);
	time = time_elapsed(philo->table, get_time());
	print_action(time, philo, "has taken a RIGHT fork", YEL);
	wait_time(philo, DEAD);
	set_status(philo, &philo->state, DEAD);
	return (NULL);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;
	long	time;

	table = data;
	if (all_thread_ready(&table->table_mtx, table->nbr_thread,
			table->nbr_of_philos))
	{
		while (!simulation_finish(table))
		{
			i = -1;
			while (++i < table->nbr_of_philos && (!simulation_finish(table)))
			{
				if (philo_died(&table->philo[i]))
				{
					set_status(&table->philo[i], &table->philo[i].state, DEAD);
					time = time_elapsed(table, get_time());
					print_action(time, table->philo, "died", RED);
					set_bool(&table->table_mtx, &table->end_simulation, true);
				}
			}
		}
	}
	return (NULL);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!simulation_finish(philo->table))
	{
		if (get_status(philo, &philo->state) != FULL && !philo_died(philo))
			eat(philo);
		if (!philo_died(philo))
			ft_sleep(philo);
		if (!philo_died(philo))
			thinking(philo);
		if (philo_died(philo))
			set_bool(&philo->table->table_mtx,
				&philo->table->end_simulation, true);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	table->start_simulation = get_time();
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
	table->nbr_thread = i;
	threads_control(pthread_create(&table->monitor, NULL, monitor_dinner,
			table), CREATE);
	i = -1;
	while (++i < table->nbr_of_philos)
		threads_control(pthread_join(table->philo[i].thread_id, NULL), JOIN);
	threads_control(pthread_join(table->monitor, NULL), JOIN);
}
