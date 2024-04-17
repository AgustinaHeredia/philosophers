/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:07:23 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/17 00:00:21 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo)
{
	long	time;

	mtx_control(pthread_mutex_lock(&philo->first_fork->fork), LOCK);
	time = time_elapsed(philo->table, get_time());
	print_action(time, philo->id_philo, "has taken a FIRST fork", YEL);
	if (get_status(philo) != DEAD)
	{
		mtx_control(pthread_mutex_lock(&philo->second_fork->fork), LOCK);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo->id_philo, "has taken a SECOND fork", YEL);
	}
	else
		mtx_control(pthread_mutex_unlock(&philo->first_fork->fork), UNLOCK);
}

void	drop_fork(t_fork *fork_right, t_fork *fork_left)
{
	mtx_control(pthread_mutex_unlock(&fork_right->fork), UNLOCK);
	mtx_control(pthread_mutex_unlock(&fork_left->fork), UNLOCK);
}

void	eat(t_philo *philo)
{
	long	time;

	take_fork(philo);
	set_status(philo, EATING);
	if (get_status(philo) != DEAD)
	{
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo->id_philo, "is sleeping", BLU);
	}
	set_long(&philo->philo_mutex, &philo->last_time_meal, get_time());
	wait_time(philo, EATING);
	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	philo->count_meals++;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	drop_fork(philo->first_fork, philo->second_fork);
}

void	thinking(t_philo *philo)
{
	long	time;

	set_status(philo, THINKING);
	if (get_status(philo) != DEAD)
	{
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo->id_philo, "is thinking", LIL);
	}
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	set_status(philo, SLEEPING);
	if (get_status(philo) != DEAD)
	{
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo->id_philo, "is sleeping", BLU);
	}
	wait_time(philo, SLEEPING);
}
