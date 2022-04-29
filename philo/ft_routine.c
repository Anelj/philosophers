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

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->lim_time_m);
	philo->lim_time = ft_gettime() + philo->stat->time_to_die;
	pthread_mutex_unlock(&philo->lim_time_m);
	if (!ft_message("%ld %d is eating.\n", philo, 0))
		return (0);
	ft_usleep((philo->stat->time_to_eat) * 1000);
	if (++(philo->meal_count) == philo->stat->num_to_eat)
	{
		pthread_mutex_lock(&philo->stat->ate_m);
		philo->stat->eat_target += philo->meal_count;
		pthread_mutex_unlock(&philo->stat->ate_m);
	}
	return (1);
}

int	ft_start_routine(t_philo *philo)
{
	if (!ft_message("%ld %d is thinking.\n", philo, 0))
		return (0);
	if (philo->stat->num != 1 && philo->i % 2 == 1)
		ft_usleep(philo->stat->time_to_eat * 1000 / 2);
	return (1);
}

int	ft_routine_process(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	if (!ft_message("%ld %d has taken a fork.\n", philo, 0)
		|| philo->stat->num == 1)
	{
		pthread_mutex_unlock(philo->lfork);
		return (0);
	}
	pthread_mutex_lock(philo->rfork);
	if (!ft_message("%ld %d has taken a fork.\n", philo, 0)
		|| !ft_eat(philo))
	{
		pthread_mutex_unlock(philo->rfork);
		pthread_mutex_unlock(philo->lfork);
		return (0);
	}
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	if (!ft_message("%ld %d is sleeping.\n", philo, 0))
		return (0);
	ft_usleep((philo->stat->time_to_sleep) * 1000);
	if (!ft_message("%ld %d is thinking.\n", philo, 0))
		return (0);
	return (1);
}

void	*ft_routine(void *vphilo)
{
	t_philo	*philo;

	philo = (t_philo *) vphilo;
	if (!ft_start_routine(philo))
		return (0);
	while (1)
	{
		if (!ft_death_check(philo->stat) || !ft_routine_process(philo))
			return (0);
		if (philo->stat->num % 2 == 1 && philo->stat->time_to_eat * 1000 * 2
			- philo->stat->time_to_sleep * 1000 > 0)
			ft_usleep(philo->stat->time_to_eat * 1000 * 2
				- philo->stat->time_to_sleep * 1000);
	}
}
