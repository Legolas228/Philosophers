/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:05:48 by pborrull          #+#    #+#             */
/*   Updated: 2024/02/21 10:05:38 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

struct	s_param;

typedef struct s_philos
{
	int						num;
	int						left_fork;
	int						right_fork;
	int						eats;
	long long				last_meal;
	pthread_mutex_t			t_eats;
	pthread_mutex_t			mut_last_meal;
	struct s_param			*param;
}	t_philos;

typedef struct s_param
{
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	int				death;
	int				phil_num;
	int				finish;
	long long		start_time;
	pthread_t		thread[201];
	pthread_mutex_t	all_eats_mut;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	printing;
	pthread_mutex_t	fork[201];
	t_philos		philosopher[201];
}	t_param;

int			ft_atoi(char *str);
void		ft_wait(int time);
int			ft_error(char *str);
int			ft_init(t_param *param, char **argv);
void		ft_prnt(t_param *param, int id, char *str);
void		*actions(void *philo);
void		death(t_param *param);
long long	cur_time(t_param *param);
long long	start_time(void);
void		ft_mutex_destroyer(t_param *param);
int			thread_start(t_param *param);
int			next_philosopher(t_param *param, int i);
int			check_die(t_param *param, int i, int time_lst_m);
void		aux(t_philos *philo);

#endif
