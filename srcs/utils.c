/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:25:55 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/16 23:50:45 by agusheredia      ###   ########.fr       */
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

	start = table->start_simulation;
	elapsed = actual_time - start;
	return (elapsed);
}

void	wait_time(t_philo *philo, t_state state)
{
	long	start;
	long	wait;

	start = get_time();
	wait = 0;
	if (state == SLEEPING)
		wait = get_long(&philo->table->table_mtx, &philo->table->time_to_sleep);
	else if (state == EATING)
		wait = get_long(&philo->table->table_mtx, &philo->table->time_to_eat);
	while ((get_time() - start) < wait)
		usleep(500);
}

void	print_action(long time, int philo_x, char *str, char *color)
{
	printf("%s%ld %d %s%s\n", color, time, philo_x, str, NC);
}
