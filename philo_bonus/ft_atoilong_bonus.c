/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgoliath <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:23:24 by mgoliath          #+#    #+#             */
/*   Updated: 2021/10/15 14:23:27 by mgoliath         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_digitstr(char *str, int *i)
{
	while ((*str == '\t' || *str == '\n' || *str == '\v'
			|| *str == '\f' || *str == '\r' || *str == ' ') && *str)
		str++;
	if (*str && (*str == '+' || *str == '-'))
	{
		if (*str == '-')
			*i = 1;
		str++;
	}
	return (str);
}

long long	ft_atoilong(char *str)
{
	int			i;
	long long	n;

	i = 0;
	n = 0;
	str = ft_digitstr(str, &i);
	if (!(*str >= '0' && *str <= '9') || !*str)
		exit(1);
	while ((*str >= '0' && *str <= '9') && *str)
	{
		if (n < 9223372036854775807 / 10
			|| (n == 9223372036854775807 / 10 && ((i != 1 && *str <= '7')
					|| (i == 1 && *str <= '8'))))
		{
			n = n * 10 + (long long)((int)*str - 48);
			str++;
		}
		else
			exit(1);
	}
	if (*str)
		exit(1);
	if (i == 1)
		n = -n;
	return (n);
}
