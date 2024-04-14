/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syncro_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusheredia <agusheredia@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:32:55 by agusheredia       #+#    #+#             */
/*   Updated: 2024/04/14 11:37:46 by agusheredia      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->table_mutex, table->all_threads_ready))
		break ;
}
