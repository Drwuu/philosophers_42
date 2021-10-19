/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:16:43 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/19 20:02:46 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	is_end(t_philo *philo)
{
	int	eat_count;

	if (pthread_mutex_lock(&(philo->datas->end_m)))
		return (set_error(philo->datas, LOCK_MUTEX_ERROR));
	eat_count = philo->datas->eat_count;
	if (pthread_mutex_unlock(&(philo->datas->end_m)))
		return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
	if (philo->datas->must_eat_count > 0 && eat_count >= \
	philo->datas->must_eat_count * philo->datas->philo_nb)
	{
		printf("Philosophers ate all meals\n");
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	is_dead(t_philo *philo)
{
	long	eat_end;
	long	time;

	time = ft_get_time();
	if (pthread_mutex_lock(&(philo->datas->end_m)))
		return (set_error(philo->datas, LOCK_MUTEX_ERROR));
	eat_end = time - philo->start_eat_time;
	if (pthread_mutex_unlock(&(philo->datas->end_m)))
		return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
	if (eat_end >= philo->datas->die_time)
	{
		message(philo, "died\n", "\033[0;31m");
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor(void *datas)
{
	t_philo	*philos;
	int		philo_nb;
	int		i;

	i = -1;
	philos = (t_philo *)datas;
	philo_nb = philos->datas->philo_nb;
	while (TRUE)
	{
		while (++i < philo_nb)
		{
			if (is_dead(&(philos[i])) || is_end(&(philos[i])))
			{
				if (pthread_mutex_lock(&(philos[i].datas->write_m)))
				{
					set_error(philos[i].datas, LOCK_MUTEX_ERROR);
					return ((void *)1);
				}
				return (NULL);
			}
		}
		usleep(1000);
		i = -1;
	}
	return (NULL);
}
