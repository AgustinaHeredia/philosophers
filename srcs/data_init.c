/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:39:38 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/09 16:52:13 by agheredi         ###   ########.fr       */
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

int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	int		res;

	i = 0;
	res = 0;
	while (i < table->number_of_philosophers)
	{
		philo = table->philo + i;
		philo->table = table;
		philo->id_philo = i + 1;
		philo->count_meals = 0;
		philo->full = false;
		philo->last_time_meal = 0;
		asigne_fork(philo, table->fork, i);
		res = mtx_error(pthread_mutex_init(&philo->philo_mutex, NULL), INIT);
		if (res != 0)
			return (1);
		i++;
	}
	return (res);
}

int	data_init(t_table *table)
{
	int	i;
	int	res;

	table->end_simulation = false;
	table->philo = malloc(sizeof(t_philo) * table->number_of_philosophers);
	if (!table->philo)
		return (ft_error("Error: malloc failed"));
	table->fork = malloc(sizeof(t_fork) * table->number_of_philosophers);
	if (!table->fork)
		return (ft_error("Error: malloc failed"));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		res = mtx_error(pthread_mutex_init(&table->fork[i].fork, NULL), INIT);
		if (res != 0)
			return (1);
		table->fork[i].id_fork = i;
		i++;
	}
	if (philo_init(table) != 0)
		return (1);
	return (0);
}
