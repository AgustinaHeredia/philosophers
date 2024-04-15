/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:07:23 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/15 15:10:48 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo *philo)
{
	int	nbr_limit_meals;

	mtx_error(pthread_mutex_lock(&philo->left_fork->fork), LOCK);
	print_action(get_time(), philo->id_philo, "has taken a LEFT fork", YEL);
	mtx_error(pthread_mutex_lock(&philo->right_fork->fork), LOCK);
	print_action(get_time(), philo->id_philo, "has taken a RIGHT fork", YEL);
	set_long(&philo->philo_mutex, &philo->last_time_meal, get_time());
	philo->count_meals++;
	print_action(get_time(), philo->id_philo, "is eating", GRE);
	ft_sleep(philo->table->time_to_sleep, philo);
	nbr_limit_meals = philo->table->number_of_times_each_philo_must_eat;
	if ((nbr_limit_meals > 0) && philo->count_meals == nbr_limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	mtx_error(pthread_mutex_unlock(&philo->left_fork->fork), UNLOCK);
	mtx_error(pthread_mutex_unlock(&philo->right_fork->fork), UNLOCK);
}

void	thinking(t_philo *philo)
{
	(void)philo;
}

void	ft_sleep(long time, t_philo *philo)
{
	long	start;
	long	elapsed;
	long	sleeping;

	start = get_time();
	while (get_time() - start < time)
	{
		if (simulation_finish(philo->table))
			break ;
		elapsed = get_time() - start;
		sleeping = time - elapsed;
		if (sleeping > 1e4)
			usleep(sleeping / 2);
		else
			while (get_time() - start < time)
				;
	}
}
