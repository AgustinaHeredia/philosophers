/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 22:07:23 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/18 17:35:29 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo)
{
	long	time;

	mtx_control(pthread_mutex_lock(philo->rigth_fork), LOCK);
	printf("--- %d del fork es %p\n", philo->id_philo, philo->rigth_fork);
	time = time_elapsed(philo->table, get_time());
	print_action(time, philo, "has taken a RIGTH fork", YEL);
	if (get_status(philo, &philo->state) != DEAD)
	{
		mtx_control(pthread_mutex_lock(philo->left_fork), LOCK);
		printf("--- %d del fork es %p\n", philo->id_philo, philo->left_fork);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "has taken a LEFT fork", YEL);
	}
	else
		mtx_control(pthread_mutex_unlock(philo->rigth_fork), UNLOCK);
	if (get_status(philo, &philo->state) != DEAD)
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
	if (get_status(philo, &philo->state) != DEAD)
	{
		set_status(philo, &philo->state, EATING);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "is eating", GRE);
	}
	set_long(&philo->philo_mutex, &philo->last_time_meal, time);
	wait_time(philo, EATING);
	mtx_control(pthread_mutex_lock(&philo->philo_mutex), LOCK);
	//wait_time(philo, EATING);
	philo->count_meals++;
	mtx_control(pthread_mutex_unlock(&philo->philo_mutex), UNLOCK);
	mtx_control(pthread_mutex_lock(&philo->table->table_mtx), LOCK);
	if (philo->count_meals == philo->table->nbr_must_eat)
		set_status(philo, &philo->state, FULL);
	mtx_control(pthread_mutex_unlock(&philo->table->table_mtx), UNLOCK);
	drop_fork(philo->rigth_fork, philo->left_fork);
}

void	thinking(t_philo *philo)
{
	long	time;

	if (get_status(philo, &philo->state) != DEAD)
	{
		set_status(philo, &philo->state, THINKING);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "is thinking", LIL);
	}
}

void	ft_sleep(t_philo *philo)
{
	long	time;

	if (get_status(philo, &philo->state) != DEAD)
	{
		set_status(philo, &philo->state, SLEEPING);
		time = time_elapsed(philo->table, get_time());
		print_action(time, philo, "is sleeping", BLU);
	}
	wait_time(philo, SLEEPING);
}
