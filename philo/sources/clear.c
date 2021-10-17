/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:09:10 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/17 18:03:42 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutexes(t_datas *datas)
{
	int	i;

	i = -1;
	while (++i < datas->philo_nb)
		if (pthread_mutex_destroy(&(datas->fork_m[i])))
			return (datas->error_type = DESTROY_MUTEX_ERROR);
	if (pthread_mutex_destroy(&(datas->eat_m)))
		return (datas->error_type = DESTROY_MUTEX_ERROR);
	if (pthread_mutex_destroy(&(datas->write_m)))
		return (datas->error_type = DESTROY_MUTEX_ERROR);
	if (pthread_mutex_destroy(&(datas->end_m)))
		return (datas->error_type = DESTROY_MUTEX_ERROR);
	return (0);
}

int	unlock_mutexes(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->datas->philo_nb)
		if (pthread_mutex_unlock(&(philo->datas->fork_m[i])))
			return (philo->datas->error_type = UNLOCK_MUTEX_ERROR);
	if (pthread_mutex_unlock(&(philo->datas->eat_m)))
		return (philo->datas->error_type = UNLOCK_MUTEX_ERROR);
	// if (pthread_mutex_unlock(&(philo->datas->write_m)))
	// 	return (philo->datas->error_type = UNLOCK_MUTEX_ERROR);
	// if (pthread_mutex_unlock(&(philo->datas->end_m)))
	// 	return (philo->datas->error_type = UNLOCK_MUTEX_ERROR);
	return (0);
}

void	clear_datas(t_philo *philos, t_datas *datas)
{
	if (datas)
	{
		if (datas->fork_m)
		{
			free(datas->fork_m);
			datas->fork_m = NULL;
		}
		datas = NULL;
	}
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
}
