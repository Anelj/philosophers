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

#include "philo.h"

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

volatile int	*ft_isdead(void)
{
	static volatile int	isdead = 0;

	return (&isdead);
}

void	ft_set_dead(t_stat *stat)
{
	pthread_mutex_lock(&stat->dead);
	*ft_isdead() = 1;
	pthread_mutex_unlock(&stat->dead);
}

int	ft_message(char *s, t_philo *philo, int to_print)
{
	pthread_mutex_lock(&philo->stat->write_m);
	pthread_mutex_lock(&philo->stat->dead);
	if (!(*ft_isdead()) || to_print)
	{
		printf(s, ft_gettime() - philo->stat->time, philo->i);
		pthread_mutex_unlock(&philo->stat->dead);
		pthread_mutex_unlock(&philo->stat->write_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->stat->dead);
	pthread_mutex_unlock(&philo->stat->write_m);
	return (0);
}
