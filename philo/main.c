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

int	ft_validate_stat(t_stat *stat)
{
	if (stat->num <= 0 || stat->time_to_sleep <= 0 || stat->time_to_eat <= 0
		|| stat->time_to_die <= 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stat	stat;

	if (argc < 5 || argc > 6)
		return (1);
	if (ft_init(&stat, argc, argv) || ft_validate_stat(&stat))
		return (1);
	if (ft_init_mutexes(&stat) || ft_init_philos(&stat))
	{
		ft_clear(&stat);
		return (1);
	}
	ft_start(&stat);
	ft_clear(&stat);
	return (0);
}
