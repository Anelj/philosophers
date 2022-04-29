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

void	ft_philo(t_stat *stat)
{
	pthread_t	tid;

	ft_init_lim_time_s(stat);
	stat->lim_time = ft_gettime() + stat->time_to_die;
	if (pthread_create(&tid, NULL, ft_time_monitor, (void *)stat) != 0)
	{
		sem_close(stat->lim_time_s);
		sem_wait(stat->write_s);
		sem_post(stat->dead_s);
		exit(1);
	}
	pthread_detach(tid);
	ft_routine(stat);
}

void	ft_clear_after_fork_er(int i, int *pids, t_stat *stat)
{
	int	j;

	if (i != 0)
		sem_wait(stat->write_s);
	j = i;
	while (--i >= 0)
		kill(pids[i], SIGKILL);
	while (--j >= 0)
		waitpid(pids[j], 0, 0);
	ft_clear(pids, stat);
	exit(1);
}

int	ft_start(t_stat *stat, int *pids)
{
	int			i;
	pthread_t	tid;

	i = 0;
	while (i < stat->num)
	{
		stat->i = i + 1;
		pids[i] = fork();
		if (pids[i] < 0)
			ft_clear_after_fork_er(i, pids, stat);
		if (pids[i] == 0)
		{
			free(pids);
			ft_philo(stat);
			exit(0);
		}
		i++;
	}
	if (stat->num_to_eat > 0)
	{
		if (pthread_create(&tid, NULL, ft_eat_monitor, (void *)stat) != 0)
			return (1);
		pthread_detach(tid);
	}
	return (0);
}

void	ft_clear(int *pids, t_stat *stat)
{
	free(pids);
	unlink("/write");
	sem_close(stat->write_s);
	unlink("/dead");
	sem_close(stat->dead_s);
	unlink("/forks");
	sem_close(stat->forks_s);
	unlink("/num_can_eat");
	sem_close(stat->num_can_eat_s);
	unlink("/ate");
	sem_close(stat->ate_s);
}

int	main(int argc, char **argv)
{
	t_stat	stat;
	int		*pids;
	int		i;

	if (argc < 5 || argc > 6)
		return (1);
	ft_init(&stat, argc, argv);
	pids = malloc(sizeof(int) * stat.num);
	if (!pids)
		exit(1);
	if (ft_start(&stat, pids))
		sem_post(stat.dead_s);
	sem_wait(stat.dead_s);
	i = 0;
	while (i < stat.num)
		kill(pids[i++], SIGKILL);
	i = 0;
	while (i < stat.num)
		waitpid(pids[i++], 0, 0);
	ft_clear(pids, &stat);
}
