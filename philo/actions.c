/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 10:52:03 by pborrull          #+#    #+#             */
/*   Updated: 2024/02/21 13:16:18 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philos *philo)
{
	aux(philo);
	pthread_mutex_unlock(&(philo->t_eats));
	pthread_mutex_lock(&(philo->mut_last_meal));
	philo->last_meal = start_time();
	pthread_mutex_unlock(&(philo->mut_last_meal));
	ft_wait(philo->param->time_eat);
	pthread_mutex_unlock(&(philo->param->fork[philo->left_fork]));
	pthread_mutex_unlock(&(philo->param->fork[philo->right_fork]));
	if (philo->eats == 0)
	{
		pthread_mutex_lock(&(philo->param->all_eats_mut));
		if (philo->param->finish == philo->param->phil_num + 1)
		{
			philo->param->finish++;
			pthread_mutex_unlock(&(philo->param->all_eats_mut));
			return ;
		}
		else
			philo->param->finish++;
		pthread_mutex_unlock(&(philo->param->all_eats_mut));
	}
}

void	routine(t_philos *philo)
{
	int	dead;

	dead = 0;
	while (philo->eats != 0)
	{
		pthread_mutex_lock(&(philo->param->death_mutex));
		dead = philo->param->death;
		pthread_mutex_unlock(&(philo->param->death_mutex));
		if (dead != 0)
			break ;
		eat(philo);
		ft_prnt(philo->param, philo->num, "is sleeping");
		ft_wait(philo->param->time_sleep);
		ft_prnt(philo->param, philo->num, "is thinking");
	}
}

int	check_die(t_param *param, int i, int time_lst_m)
{
	if (time_lst_m >= param->time_die)
	{
		pthread_mutex_lock(&(param->death_mutex));
		param->death = 1;
		pthread_mutex_unlock(&(param->death_mutex));
		pthread_mutex_lock(&(param->printing));
		printf("%lld %d died\n", cur_time(param), i);
		pthread_mutex_unlock(&(param->printing));
		return (1);
	}
	return (0);
}

void	death(t_param *param)
{
	int	i;
	int	time_lst_m;

	i = 1;
	while (i <= param->phil_num && param->phil_num > 1)
	{
		pthread_mutex_lock(&(param->philosopher[i].mut_last_meal));
		time_lst_m = (start_time() - param->philosopher[i].last_meal);
		pthread_mutex_unlock(&(param->philosopher[i].mut_last_meal));
		pthread_mutex_lock(&(param->all_eats_mut));
		if (param->phil_num == param->finish)
		{
			pthread_mutex_unlock(&(param->all_eats_mut));
			break ;
		}
		pthread_mutex_unlock(&(param->all_eats_mut));
		if (check_die(param, i, time_lst_m) == 1)
			break ;
		if (++i > param->phil_num)
			i = 1;
	}
}

void	*actions(void *philo_void)
{
	t_philos	*philo;

	philo = (t_philos *)philo_void;
	if (philo->param->phil_num == 1)
	{
		ft_wait(philo->param->time_die);
		printf("%d 1 died\n", philo->param->time_die);
		return (NULL);
	}
	if (philo->num % 2)
	{
		pthread_mutex_lock(&(philo->mut_last_meal));
		philo->last_meal = start_time();
		pthread_mutex_unlock(&(philo->mut_last_meal));
		ft_wait(15);
	}
	else
	{
		pthread_mutex_lock(&(philo->mut_last_meal));
		philo->last_meal = start_time();
		pthread_mutex_unlock(&(philo->mut_last_meal));
	}
	routine(philo);
	return (NULL);
}
