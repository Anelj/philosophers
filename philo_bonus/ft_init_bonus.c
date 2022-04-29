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

void	ft_init_lim_time_s(t_stat *stat)
{
	char		c[3];

	c[0] = '/';
	c[1] = (char)stat->i;
	c[2] = '\0';
	sem_unlink("/lin");
	stat->lim_time_s = sem_open("/lin", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (!stat->lim_time_s)
	{
		sem_wait(stat->write_s);
		sem_post(stat->dead_s);
		exit(1);
	}
}

int	ft_init_sems(t_stat *stat)
{
	sem_unlink("/forks");
	stat->forks_s = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, stat->num);
	sem_unlink("/num_can_eat");
	stat->num_can_eat_s = sem_open("/num_can_eat", O_CREAT | O_EXCL, S_IRWXU,
			stat->num / 2);
	sem_unlink("/ate");
	stat->ate_s = sem_open("/ate", O_CREAT | O_EXCL, S_IRWXU, 0);
	sem_unlink("/dead");
	stat->dead_s = sem_open("/dead", O_CREAT | O_EXCL, S_IRWXU, 0);
	sem_unlink("/write");
	stat->write_s = sem_open("/write", O_CREAT | O_EXCL, S_IRWXU,
			1);
	if (!stat->write_s || !stat->forks_s || !stat->num_can_eat_s || !stat->ate_s
		|| !stat->dead_s)
	{
		perror("errno\n");
		return (1);
	}
	return (0);
}

int	ft_validate_stat(t_stat *stat)
{
	if (stat->num <= 0 || stat->time_to_sleep <= 0 || stat->time_to_eat <= 0
		|| stat->time_to_die <= 0)
		exit(1);
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
	stat->lim_time = 0;
	stat->time = ft_gettime();
	ft_validate_stat(stat);
	ft_init_sems(stat);
	return (0);
}
