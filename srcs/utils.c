/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:25:55 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/22 12:41:07 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long)time.tv_sec * 1000 + time.tv_usec / 1000);
}

long	time_elapsed(t_table *table, long actual_time)
{
	long	elapsed;
	long	start;

	start = get_long(&table->time_mtx, &table->start_simulation);
	elapsed = actual_time - start;
	return (elapsed);
}

void	wait_time(long wait_t)
{
	long	start;
	long	wait;

	start = get_time();
	wait = wait_t;
	while ((get_time() - start) < wait)
		usleep(100);
}

void	print_action(long time, t_philo *philo, char *str, char *color)
{
	mtx_control(pthread_mutex_lock(&philo->table->table_mtx), LOCK);
	if (philo->table->end_simulation == false && philo->state != DEAD)
		printf("%s%ld %d %s%s\n", color, time, philo->id_philo, str, NC);
	mtx_control(pthread_mutex_unlock(&philo->table->table_mtx), UNLOCK);
}
