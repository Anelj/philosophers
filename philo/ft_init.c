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

void	ft_clear(t_stat *stat)
{
	int	i;

	i = 0;
	while (i < stat->num)
	{
		pthread_mutex_destroy(&stat->philos[i].lim_time_m);
		pthread_mutex_destroy(&stat->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&stat->ate_m);
	pthread_mutex_destroy(&stat->write_m);
	pthread_mutex_destroy(&stat->dead);
	free(stat->forks);
	free(stat->philos);
}

void	ft_init_philo_forks(t_stat *stat, int i)
{
	if (i != 0)
	{
		stat->philos[i].lfork = &stat->forks[(i + 1) % stat->num];
		stat->philos[i].rfork = &stat->forks[i];
	}
	else
	{
		stat->philos[i].lfork = &stat->forks[i];
		stat->philos[i].rfork = &stat->forks[(i + 1) % stat->num];
	}
}

int	ft_init_philos(t_stat *stat)
{
	int	i;

	stat->philos = malloc(sizeof(t_philo) * (stat->num));
	if (stat->philos == NULL)
		return (1);
	i = 0;
	while (i < stat->num)
	{
		stat->philos[i].i = i + 1;
		stat->philos[i].meal_count = 0;
		stat->philos[i].stat = stat;
		stat->philos[i].lim_time = ft_gettime() + stat->time_to_die;
		if (pthread_mutex_init(&stat->philos[i].lim_time_m, NULL))
			return (1);
		ft_init_philo_forks(stat, i);
		i++;
	}
	return (0);
}

int	ft_init_mutexes(t_stat *stat)
{
	int	i;

	i = 0;
	stat->philos = NULL;
	stat->forks = malloc(sizeof(pthread_mutex_t) * stat->num);
	if (!(stat->forks))
		return (1);
	while (i < stat->num)
	{
		if (pthread_mutex_init(&stat->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&stat->ate_m, NULL)
		|| pthread_mutex_init(&stat->dead, NULL)
		|| pthread_mutex_init(&stat->write_m, NULL))
		return (1);
	return (0);
}

int	ft_init(t_stat *stat, int argc, char **argv)
{
	stat->num = (int)ft_atoilong(argv[1]);
	stat->time_to_die = ft_atoilong(argv[2]);
	stat->time_to_eat = ft_atoilong(argv[3]);
	stat->time_to_sleep = ft_atoilong(argv[4]);
	if (argc == 6)
		stat->num_to_eat = (int)ft_atoilong(argv[5]);
	else
		stat->num_to_eat = -1;
	stat->eat_target = 0;
	stat->time = ft_gettime();
	return (0);
}
