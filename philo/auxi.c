/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 12:30:04 by pborrull          #+#    #+#             */
/*   Updated: 2024/02/21 09:25:35 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *str)
{
	write(2, "Error", 5);
	printf("\n%s\n", str);
	return (1);
}

long long	cur_time(t_param *param)
{
	struct timeval	cur;

	gettimeofday(&cur, NULL);
	return (((cur.tv_sec * 1000) + (cur.tv_usec / 1000)) - param->start_time);
}

long long	start_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_prnt(t_param *param, int id, char *str)
{
	pthread_mutex_lock(&(param->death_mutex));
	pthread_mutex_lock(&(param->all_eats_mut));
	if (param->death != 1 && param->finish != param->phil_num)
	{
		pthread_mutex_lock(&(param->printing));
		printf("%lld %d %s\n", cur_time(param), id, str);
		pthread_mutex_unlock(&(param->printing));
	}
	pthread_mutex_unlock(&(param->death_mutex));
	pthread_mutex_unlock(&(param->all_eats_mut));
}

int	ft_atoi(char *str)
{
	int	i;
	int	signo;
	int	r;

	r = 0;
	i = 0;
	signo = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		signo = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			r = r * 10 + (str[i++] - '0');
		else
			return (-1);
	}
	return (r * signo);
}
