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

void	*ft_eat_monitor(void *vstat)
{
	t_stat	*stat;
	int		ate_count;

	stat = (t_stat *)vstat;
	ate_count = 0;
	while (1)
	{
		sem_wait(stat->ate_s);
		if (++ate_count >= stat->num)
		{
			sem_wait(stat->write_s);
			sem_post(stat->dead_s);
			break ;
		}
	}
	return (0);
}

void	*ft_time_monitor(void *vstat)
{
	t_stat	*stat;

	stat = (t_stat *)vstat;
	while (1)
	{
		ft_usleep(300);
		sem_wait(stat->lim_time_s);
		if (stat->lim_time < ft_gettime())
		{
			sem_wait(stat->write_s);
			printf("%ld %i is dead.\n", ft_gettime() - stat->time, stat->i);
			sem_post(stat->dead_s);
			sem_post(stat->lim_time_s);
			return (0);
		}
		sem_post(stat->lim_time_s);
	}
	return (0);
}

void	ft_eating_routine(t_stat *stat)
{
	sem_wait(stat->num_can_eat_s);
	sem_wait(stat->forks_s);
	ft_message("%ld %d has taken a fork.\n", stat);
	sem_wait(stat->forks_s);
	ft_message("%ld %d has taken a fork.\n", stat);
	sem_wait(stat->lim_time_s);
	stat->lim_time = ft_gettime() + stat->time_to_die;
	sem_post(stat->lim_time_s);
	ft_message("%ld %d is eating.\n", stat);
	ft_usleep(stat->time_to_eat * 1000);
	sem_post(stat->forks_s);
	sem_post(stat->forks_s);
	sem_post(stat->num_can_eat_s);
}

int	ft_routine(t_stat *stat)
{
	int	ate_count;

	ate_count = 0;
	ft_message("%ld %d is thinking.\n", stat);
	if (stat->num != 1 && stat->i % 2 == 1)
		ft_usleep(stat->time_to_eat * 1000 / 2);
	while (1)
	{
		ft_eating_routine(stat);
		if (++ate_count == stat->num_to_eat)
			sem_post(stat->ate_s);
		ft_message("%ld %d is sleeping.\n", stat);
		ft_usleep(stat->time_to_sleep * 1000);
		ft_message("%ld %d is thinking.\n", stat);
		if (stat->num < 17 && stat->num % 2 == 1
			&& stat->time_to_eat * 1000 * 2 - stat->time_to_sleep * 1000 > 0)
			ft_usleep(stat->time_to_eat * 1000 * 2
				- stat->time_to_sleep * 1000);
	}
}
