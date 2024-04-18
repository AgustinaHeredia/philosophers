/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:03 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/18 17:40:16 by agheredi         ###   ########.fr       */
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
	while (!simulation_finish(table))
	{
		i = 0;
		while (i < table->nbr_of_philos && (!simulation_finish(table)))
		{
			if (philo_died(&table->philo[i]))
			{
				set_status(&table->philo[i], &table->philo[i].state, DEAD);
				time = time_elapsed(table, get_time());
				print_action(time, table->philo, "died", RED);
				set_bool(&table->table_mtx, &table->end_simulation, true);
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
	//wait_all_threads(philo->table);
	while (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
	{
		if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
			eat(philo);
		if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
			ft_sleep(philo);
		if (!get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
			thinking(philo);
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
			if (i % 2 == 0)
				usleep(100);
		}
	}
	table->nbr_thread = i;
	monitor_dinner(table);
	//threads_control(pthread_create(&table->monitor, NULL, monitor_dinner,
	//		table), CREATE);
	i = -1;
	while (++i < table->nbr_of_philos)
		threads_control(pthread_join(table->philo[i].thread_id, NULL), JOIN);
	// threads_control(pthread_join(table->monitor, NULL), JOIN);
}
