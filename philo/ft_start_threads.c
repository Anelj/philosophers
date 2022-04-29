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

void	ft_pthread_create_fails(pthread_t *tid, int i, t_stat *stat)
{
	pthread_mutex_lock(&stat->dead);
	*ft_isdead() = 1;
	pthread_mutex_unlock(&stat->dead);
	while (--i >= 0)
		pthread_join(tid[i], 0);
	free(tid);
}

int	ft_fill_tids(pthread_t *tid, t_stat *stat)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (stat->num_to_eat > 0)
	{
		j = 1;
		if (pthread_create(tid, NULL, ft_eat_monitor, (void *)stat) != 0)
		{
			free(tid);
			return (1);
		}
	}
	while (i < stat->num)
	{
		if (pthread_create((tid + i + j), NULL, ft_routine,
				(void *)&stat->philos[i]))
		{
			ft_pthread_create_fails(tid, i, stat);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_start(t_stat *stat)
{
	int			i;
	pthread_t	*tid;
	pthread_t	tid_m;
	int			j;

	i = 0;
	j = 0;
	if (stat->num_to_eat > 0)
		j = 1;
	tid = malloc(sizeof(pthread_t) * (stat->num + j));
	if (!tid || ft_fill_tids(tid, stat))
		return ;
	if (pthread_create(&tid_m, NULL, ft_time_monitor, (void *) stat) != 0)
		ft_set_dead(stat);
	else
		pthread_join(tid_m, 0);
	while (i < stat->num + j)
		pthread_join(tid[i++], 0);
	free(tid);
}
