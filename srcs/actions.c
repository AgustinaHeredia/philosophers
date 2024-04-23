/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:07:23 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/22 18:29:20 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo)
{
	long	time;

	mtx_control(pthread_mutex_lock(philo->rigth_fork), LOCK);
	time = time_elapsed(philo->table, get_time());
	// print_action(time, philo, "has taken a RIGTH fork", YEL);
	if (get_status(philo, &philo->state) != DEAD)
	{
		mtx_control(pthread_mutex_lock(philo->left_fork), LOCK);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "has taken a fork", YEL);
	}
	else
		mtx_control(pthread_mutex_unlock(philo->rigth_fork), UNLOCK);
	if (get_status(philo, &philo->state) == DEAD)
		drop_fork(philo->rigth_fork, philo->left_fork);
}

void	drop_fork(t_mtx *fork_right, t_mtx *fork_left)
{
	mtx_control(pthread_mutex_unlock(fork_right), UNLOCK);
	mtx_control(pthread_mutex_unlock(fork_left), UNLOCK);
}

void	eat(t_philo *philo)
{
	long	time;

	time = time_elapsed(philo->table, get_time());
	take_fork(philo);
	if (get_status(philo, &philo->state) != DEAD
		&& (get_status(philo, &philo->state) != FULL))
	{
		set_status(philo, &philo->state, EATING);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "is eating", GRE);
	}
	set_long(&philo->philo_mutex, &philo->last_time_meal, time);
	wait_time(philo->table->time_to_eat);
	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	philo->count_meals++;
	if (philo->count_meals == philo->table->nbr_must_eat)
		philo->philo_full = true;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	mtx_control(pthread_mutex_lock(&philo->table->table_mtx), LOCK);
	if (philo->count_meals == philo->table->nbr_must_eat)
		set_status(philo, &philo->state, FULL);
	mtx_control(pthread_mutex_unlock(&philo->table->table_mtx), UNLOCK);
	drop_fork(philo->rigth_fork, philo->left_fork);
	ft_sleep(philo);
}

void	thinking(t_philo *philo)
{
	long	time;

	if (get_status(philo, &philo->state) != DEAD)
	{
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "is thinking", LIL);
		set_status(philo, &philo->state, THINKING);
	}
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	if (get_status(philo, &philo->state) != DEAD)
	{
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "is sleeping", BLU);
		set_status(philo, &philo->state, SLEEPING);
	}
	else if (get_status(philo, &philo->state) == DEAD
		|| get_bool(&philo->table->table_mtx, &philo->table->end_simulation))
		mtx_control(pthread_mutex_unlock(philo->rigth_fork), UNLOCK);
	wait_time(get_long(&philo->table->table_mtx, &philo->table->time_to_sleep));
}
