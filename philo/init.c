/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:00:05 by pborrull          #+#    #+#             */
/*   Updated: 2024/02/28 11:46:17 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_param *param)
{
	int	i;

	i = 1;
	while (i <= param->phil_num)
	{
		if (pthread_mutex_init(&(param->fork[i]), NULL)
			|| pthread_mutex_init(&(param->philosopher[i].mut_last_meal), NULL)
			|| pthread_mutex_init(&(param->philosopher[i].t_eats), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(param->printing), NULL)
		|| pthread_mutex_init(&(param->death_mutex), NULL)
		|| pthread_mutex_init(&(param->all_eats_mut), NULL))
		return (1);
	return (0);
}

int	init_philo(t_param *param)
{
	int	i;

	i = param->phil_num ;
	while (i > 0)
	{
		param->philosopher[i].num = i;
		param->philosopher[i].left_fork = i;
		param->philosopher[i].right_fork = (i % param->phil_num) + 1;
		param->philosopher[i].last_meal = -1;
		param->philosopher[i].eats = param->times_eat;
		param->philosopher[i--].param = param;
	}
	return (0);
}

int	ft_init(t_param *param, char **argv)
{
	param->phil_num = ft_atoi(argv[1]);
	param->time_die = ft_atoi(argv[2]);
	param->time_eat = ft_atoi(argv[3]);
	param->time_sleep = ft_atoi(argv[4]);
	param->death = 0;
	param->start_time = start_time();
	param->times_eat = -1;
	if (argv[5])
		param->times_eat = ft_atoi(argv[5]);
	if (param->phil_num < 1 || param->phil_num > 200
		|| param->time_die < 0 || param->time_eat < 0
		|| param->time_sleep < 0 || (argv[5] && param->times_eat < 1))
		return (1);
	init_philo(param);
	if (init_mutex(param) == 1)
		return (1);
	return (0);
}

int	thread_start(t_param *param)
{
	int			i;

	i = 0;
	while (i++ < param->phil_num)
	{
		if (pthread_create(&param->thread[i], NULL, actions,
				(void *)&param->philosopher[i]) != 0)
			return (1);
	}
	death(param);
	return (0);
}
