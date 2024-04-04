/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agheredi <agheredi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:31:31 by agheredi          #+#    #+#             */
/*   Updated: 2024/04/04 15:56:02 by agheredi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_char(char *argv)
{
	if (!(*argv == '+' || *argv == '-'
			|| (*argv >= '0' && *argv <= '9')))
		return (1);
	if ((*argv == '+' || *argv == '-')
		&& !(argv[1] >= '0' && argv[1] <= '9'))
		return (1);
	while (*++argv)
	{
		if (!(*argv >= '0' && *argv <= '9'))
			return (1);
	}
	return (0);
}

long long	ft_atol(const char *str)
{
	long long	i;
	long long	nbr;
	int			flag;

	i = 0;
	nbr = 0;
	flag = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		flag = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		nbr = (str[i] - '0') + nbr * 10;
		i++;
	}
	if (flag == -1)
		nbr = nbr * flag;
	return (nbr);
}

int	ft_isdigit(int c)
{
	int	result;

	result = 0;
	if (c > 47 && c < 58)
	{
		result = 2048;
	}
	return (result);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
