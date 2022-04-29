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

void	ft_usleep(long l)
{
	long	now;
	long	start;

	start = ft_gettime();
	now = ft_gettime();
	while ((now * 1000 - start * 1000) < l)
	{
		usleep(10);
		now = ft_gettime();
	}
}

long	ft_gettime(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((long)now.tv_sec * 1000 + (long)now.tv_usec / 1000);
}

int	ft_message(char *s, t_stat *stat)
{
	sem_wait(stat->write_s);
	printf(s, ft_gettime() - stat->time, stat->i);
	sem_post(stat->write_s);
	return (0);
}
