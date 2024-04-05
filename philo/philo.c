/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pborrull <pborrull@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:05:15 by pborrull          #+#    #+#             */
/*   Updated: 2024/02/15 14:04:30 by pborrull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc != 5 && argc != 6)
		return (ft_error("Check the number of args!"));
	if (ft_init(&param, argv))
		return (ft_error("Something was wrong... Change the args!"));
	if (thread_start(&param) == 1)
		return (ft_error("We cannot create the threads"));
	ft_mutex_destroyer(&param);
	return (0);
}
