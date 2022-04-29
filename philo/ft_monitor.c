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

int	ft_death_check(t_stat *stat)
{
	pthread_mutex_lock(&stat->dead);
	if (*ft_isdead())
	{
		pthread_mutex_unlock(&stat->dead);
		return (0);
	}
	pthread_mutex_unlock(&stat->dead);
	return (1);
}

static void	ft_print_dead(t_stat *stat, int i)
{
	pthread_mutex_lock(&stat->dead);
	if (!(*ft_isdead()))
		*ft_isdead() = 1;
	else
	{
		pthread_mutex_unlock(&stat->dead);
		return ;
	}
	pthread_mutex_unlock(&stat->dead);
	ft_message("%ld %d is dead.\n", &stat->philos[i], 1);
}

void	*ft_time_monitor(void *vstat)
{
	t_stat	*stat;
	int		i;

	stat = (t_stat *)vstat;
	while (1)
	{
		i = 0;
		while (i < stat->num)
		{
			pthread_mutex_lock(&stat->philos[i].lim_time_m);
			if (stat->philos[i].lim_time < ft_gettime())
			{
				ft_print_dead(stat, i);
				pthread_mutex_unlock(&stat->philos[i].lim_time_m);
				return (0);
			}
			pthread_mutex_unlock(&stat->philos[i].lim_time_m);
			ft_usleep(100);
			if (!ft_death_check(stat))
				return (0);
			i++;
		}
	}
}

void	*ft_eat_monitor(void *vstat)
{
	t_stat	*stat;

	stat = (t_stat *)vstat;
	while (1)
	{
		if (!ft_death_check(stat))
			return (0);
		ft_usleep(100);
		pthread_mutex_lock(&stat->ate_m);
		if (stat->eat_target >= stat->num * stat->num_to_eat)
		{
			pthread_mutex_lock(&stat->dead);
			*ft_isdead() = 1;
			pthread_mutex_unlock(&stat->dead);
			pthread_mutex_unlock(&stat->ate_m);
			break ;
		}
		pthread_mutex_unlock(&stat->ate_m);
	}
	return (0);
}
