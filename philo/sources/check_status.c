/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:16:43 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/17 18:02:47 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_bool	is_end(t_philo *philo)
{
	if (philo->datas->must_eat_count > 0 && \
	philo->datas->eat_count >= \
	philo->datas->must_eat_count * philo->datas->philo_nb)
	{
		philo->datas->is_end = TRUE;
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
	eat_end = time - philo->start_eat_time - 5;
	if (!philo->start_eating && eat_end >= philo->datas->die_time)
	{
		pthread_mutex_lock(&(philo->datas->end_m));
		message(philo, "died\n", "\033[0;31m");
		philo->datas->dead = TRUE;
		return (TRUE);
	}
	return (FALSE);
}

void	*monitor(void *datas)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = (t_philo *)datas;
	while (TRUE)
	{
		while (++i < philos->datas->philo_nb)
		{
			if (is_dead(&(philos[i])) || is_end(&(philos[i])))
			{
				if (pthread_mutex_unlock(&(philos->datas->end_m)))
					return ((void *)1);
				if (unlock_mutexes(philos))
					return ((void *)1);
				return (NULL);
			}
		}
		if (usleep(1000))
			return ((void *)1);
		i = -1;
	}
	return (NULL);
}
