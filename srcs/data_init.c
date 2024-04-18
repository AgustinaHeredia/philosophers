/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:39:38 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/18 17:24:36 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	malloc_control(t_table *table)
{
	int	i;

	i = table->nbr_of_philos;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * i);
	if (!table->philo)
		return (ft_error("Error: malloc failed Philosopher"));
	table->fork = (t_mtx *)malloc(sizeof(t_mtx) * i);
	if (!table->fork)
	{
		free(table->philo);
		return (ft_error("Error: malloc failed Forks"));
	}
	return (0);
}

void	asigne_fork(t_philo *philo, t_mtx *fork, int position)
{
	int	philo_nrb;

	philo_nrb = philo->table->nbr_of_philos;
	if (philo_nrb == 1)
		philo->rigth_fork = &fork[position];
	else
	{
		philo->rigth_fork = &fork[position];
		if (position == (philo_nrb - 1))
			philo->left_fork = &fork[0];
		else
			philo->left_fork = &fork[(position + 1)];
	}
}

int	philo_init(t_table *table)
{
	int		i;
	t_philo	*philo;
	int		res;

	i = 0;
	res = 0;
	while (i < table->nbr_of_philos)
	{
		philo = table->philo + i;
		philo->table = table;
		philo->id_philo = i + 1;
		philo->count_meals = 0;
		philo->state = IDLE;
		philo->last_time_meal = 0;
		asigne_fork(philo, table->fork, i);
		res = mtx_control(pthread_mutex_init(&philo->philo_mutex, NULL), INIT);
		if (res != 0)
			return (1);
		i++;
	}
	return (res);
}

int	table_init(t_table *table)
{
	int	res;

	res = 0;
	table->end_simulation = false;
	table->all_philo_ready = false;
	table->nbr_thread = 0;
	table->start_simulation = 0;
	if (malloc_control(table) != 0)
		return (1);
	res = mtx_control(pthread_mutex_init(&table->table_mtx, NULL), INIT);
	if (res != 0)
		return (1);
	return (res);
}

int	data_init(t_table *table)
{
	int	i;
	int	res;

	if (table->nbr_of_philos == 0)
		return (1);
	res = table_init(table);
	if (res != 0)
		return (1);
	i = -1;
	while (++i < table->nbr_of_philos)
	{
		res = mtx_control(pthread_mutex_init(&table->fork[i], NULL), INIT);
		if (res != 0)
			return (1);
	}
	if (philo_init(table) != 0)
		return (1);
	return (0);
}
