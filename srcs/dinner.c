/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:21:03 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/15 15:55:56 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	mtx_error(pthread_mutex_lock(&philo->right_fork->fork), LOCK);
	print_action(get_time(), philo->id_philo, "has taken a RIGHT fork", YEL);
	set_bool(&philo->table->table_mutex, &philo->table->end_simulation, true);
	print_action(get_time(), philo->id_philo, "died", RED);
	return (NULL);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = data;
	while (!simulation_finish(table))
	{
		i = -1;
		while (++i < table->number_of_philosophers
			&& (!simulation_finish(table)))
		{
			if (philo_died(table->philo + i))
			{
				set_bool(&table->table_mutex, &table->end_simulation, true);
				print_action(get_time(), table->philo->id_philo, "died", RED);
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
	set_long(&philo->philo_mutex, &philo->last_time_meal, get_time());
	while (!simulation_finish(philo->table))
	{
		if (get_bool(&philo->philo_mutex, philo->full))
			break ;
		eat(philo);
		print_action(get_time(), philo->id_philo, "is sleeping", BLU);
		ft_sleep(philo->table->time_to_sleep, philo);
		thinking(philo);
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->number_of_times_each_philo_must_eat == 0)
		return ;
	else if (table->number_of_philosophers == 1)
		threads_error(pthread_create(&table->philo[0].thread_id, NULL,
				one_philo, &table->philo[0]), CREATE);
	else
	{
		while (++i < table->number_of_philosophers)
			threads_error(pthread_create(&table->philo[i].thread_id, NULL,
					dinner_simulation, &table->philo[i]), CREATE);
	}
	threads_error(pthread_create(&table->monitor, NULL,
			monitor_dinner, table), CREATE);
	table->start_simulation = get_time();
	set_bool(&table->table_mutex, &table->all_philo_ready, true);
	i = -1;
	while (++i < table->number_of_philosophers)
		threads_error(pthread_join(table->philo[i].thread_id, NULL), JOIN);
	set_bool(&table->table_mutex, &table->end_simulation, true);
	printf("HA LLEGADO AQUI\n");
	threads_error(pthread_join(table->monitor, NULL), JOIN);
	printf("HA LLEGADO despues del join monitor\n");
}
