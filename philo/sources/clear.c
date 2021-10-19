/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:09:10 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/19 20:22:48 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutexes(t_datas *datas)
{
	int	i;

	i = -1;
	while (++i < datas->philo_nb)
		if (pthread_mutex_destroy(&(datas->fork_m[i])))
			set_error(datas, DESTROY_MUTEX_ERROR);
	if (pthread_mutex_destroy(&(datas->eat_m)))
		set_error(datas, DESTROY_MUTEX_ERROR);
	if (pthread_mutex_destroy(&(datas->write_m)))
		set_error(datas, DESTROY_MUTEX_ERROR);
	if (pthread_mutex_destroy(&(datas->end_m)))
		set_error(datas, DESTROY_MUTEX_ERROR);
	return (datas->error_type);
}

void	clear_datas(t_philo *philos, t_datas *datas)
{
	if (datas)
	{
		if (destroy_mutexes(datas))
			printf("Error of type DESTROY_MUTEX_ERROR:\n"
				"Mutex destroy failed\n");
		if (datas->fork_m)
			free(datas->fork_m);
		free(datas);
		datas = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}
