/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:39:38 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/08 22:18:59 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	asigne_fork(t_philo *philo, t_fork *fork, int position)
{
	int	philo_nrb;

	philo_nrb = philo->table->number_of_philosophers;
	philo->left_fork = &fork[(position + 1) % philo_nrb];
	philo->right_fork = &fork[position];
	if (philo_nrb % 2 == 0)
	{
		philo->right_fork = &fork[position];
		philo->left_fork = &fork[(position + 1) % philo_nrb];
	}
}

void	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < table->number_of_philosophers)
	{
		philo = table->philo + i;
		philo->id_philo = i + 1;
		philo->count_meals = 0;
		philo->full = false;
		philo->last_time_meal = 0;
		asigne_fork(philo, table->fork, i);
		handle_mutex_error(pthread_mutex_init(&philo->thread_id, NULL), INIT);
		philo->table = table;
		i++;
	}
}

void	data_init(t_table *table)
{
	int	i;

	table->end_simulation = false;
	table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!table->philo)
		ft_error("Error: malloc failed");
	table->fork = malloc(sizeof(t_fork) * table->number_of_philosophers);
	if (!table->fork)
		ft_error("Error: malloc failed");
	i = 0;
	while (i < table->number_of_philosophers)
	{
		handle_mutex_error(pthread_mutex_init(&table->fork[i], NULL), INIT);
		table->fork[i].id_fork = i;
		i++;
	}
	philo_init(table);
}
