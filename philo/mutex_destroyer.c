/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_destroyer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:40:49 by pborrull          #+#    #+#             */
/*   Updated: 2024/02/21 13:16:47 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_destroyer(t_param *param)
{
	int	i;

	i = 1;
	while (i <= param->phil_num)
		pthread_join(param->thread[i++], NULL);
	i = 1;
	while (i <= param->phil_num)
	{
		pthread_mutex_destroy(&param->fork[i]);
		pthread_mutex_destroy(&param->philosopher[i].mut_last_meal);
		pthread_mutex_destroy(&param->philosopher[i++].t_eats);
	}
	pthread_mutex_destroy(&(param->printing));
	pthread_mutex_destroy(&(param->death_mutex));
	pthread_mutex_destroy(&(param->all_eats_mut));
	return ;
}

void	aux(t_philos *philo)
{
	pthread_mutex_lock(&(philo->param->fork[philo->left_fork]));
	pthread_mutex_lock(&(philo->param->fork[philo->right_fork]));
	ft_prnt(philo->param, philo->num, "has taken a fork");
	ft_prnt(philo->param, philo->num, "has taken a fork");
	pthread_mutex_lock(&(philo->t_eats));
	philo->eats--;
	ft_prnt(philo->param, philo->num, "is eating");
}

void	ft_wait(int time)
{
	long long	now;

	now = start_time();
	while ((start_time() - now) < (long long)time)
		usleep(500);
}
