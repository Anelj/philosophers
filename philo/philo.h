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

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>

typedef struct s_philo
{
	int				i;
	int				meal_count;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	lim_time_m;
	long			lim_time;
	struct s_stat	*stat;
}	t_philo;

typedef struct s_stat
{
	int				num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time;
	int				num_to_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	ate_m;
	pthread_mutex_t	dead;
	pthread_mutex_t	write_m;
	volatile int	eat_target;
	t_philo			*philos;
}	t_stat;

long long		ft_atoilong(char *str);
int				ft_init(t_stat *stat, int argc, char **argv);
int				ft_validate_stat(t_stat *stat);
long			ft_gettime(void);
void			ft_clear(t_stat *stat);
volatile int	*ft_isdead(void);
int				ft_message(char *s, t_philo *philo, int to_print);
void			*ft_time_monitor(void *vstat);
void			*ft_eat_monitor(void *vstat);
int				ft_init_mutexes(t_stat *stat);
int				ft_init_philos(t_stat *stat);
int				ft_death_check(t_stat *stat);
void			ft_set_dead(t_stat *stat);
void			ft_start(t_stat *stat);
void			*ft_routine(void *vphilo);
int				ft_validate_stat(t_stat *stat);
void			ft_usleep(long l);

#endif
