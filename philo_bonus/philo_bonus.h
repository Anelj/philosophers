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

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_stat
{
	int				i;
	int				num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				num_to_eat;
	long			time;
	sem_t			*forks_s;
	sem_t			*num_can_eat_s;
	sem_t			*ate_s;
	sem_t			*dead_s;
	sem_t			*write_s;
	sem_t			*lim_time_s;
	volatile long	lim_time;
	volatile int	eat_target;
	volatile int	isdead;
}	t_stat;

int			ft_init(t_stat *stat, int argc, char **argv);
long long	ft_atoilong(char *str);
long		ft_gettime(void);
int			ft_message(char *s, t_stat *stat);
int			ft_init_sems(t_stat *stat);
void		ft_init_lim_time_s(t_stat *stat);
void		*ft_eat_monitor(void *vstat);
void		*ft_time_monitor(void *vstat);
void		ft_eating_routine(t_stat *stat);
int			ft_routine(t_stat *stat);
void		ft_clear(int *pids, t_stat *stat);
void		ft_usleep(long l);

#endif
