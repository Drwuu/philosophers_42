/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:24:48 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/19 19:03:50 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	message(t_philo *philo, const char *msg, const char *color)
{
	long	time;

	time = 0;
	if (philo->datas->dead || philo->datas->is_end)
	{
		if (pthread_mutex_lock(&(philo->datas->end_m)))
			return (set_error(philo->datas, LOCK_MUTEX_ERROR));
		philo->datas->dead = TRUE;
		if (pthread_mutex_unlock(&(philo->datas->end_m)))
			return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
		return (0);
	}
	if (pthread_mutex_lock(&(philo->datas->write_m)))
		return (set_error(philo->datas, LOCK_MUTEX_ERROR));
	time = ft_get_time();
	time = time - philo->datas->start_time_simul;
	printf("%.5ld %s%d %s\033[0m", time, color, philo->id + 1, msg);
	if (pthread_mutex_unlock(&(philo->datas->write_m)))
		return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
	return (0);
}

int	think(t_philo *philo)
{
	if (philo->datas->dead || philo->datas->is_end)
	{
		if (pthread_mutex_lock(&(philo->datas->end_m)))
			return (set_error(philo->datas, LOCK_MUTEX_ERROR));
		philo->datas->dead = TRUE;
		if (pthread_mutex_unlock(&(philo->datas->end_m)))
			return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
		return (0);
	}
	if (message(philo, "is thinking\n", "\033[0;35m"))
		return (1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->datas->dead || philo->datas->is_end)
	{
		if (pthread_mutex_lock(&(philo->datas->end_m)))
			return (set_error(philo->datas, LOCK_MUTEX_ERROR));
		philo->datas->dead = TRUE;
		if (pthread_mutex_unlock(&(philo->datas->end_m)))
			return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
		return (0);
	}
	if (pthread_mutex_lock(&(philo->datas->fork_m[philo->forkL])))
		return (set_error(philo->datas, LOCK_MUTEX_ERROR));
	if (pthread_mutex_lock(&(philo->datas->fork_m[philo->forkR])))
		return (set_error(philo->datas, LOCK_MUTEX_ERROR));
	if (message(philo, "has taken a fork\n", "\033[0;36m"))
		return (-1);
	if (message(philo, "has taken a fork\n", "\033[0;36m"))
		return (-1);
	return (0);
}

int	drop_forks_n_sleep(t_philo *philo)
{
	long	time;

	time = 0;
	if (philo->datas->dead || philo->datas->is_end)
	{
		if (pthread_mutex_lock(&(philo->datas->end_m)))
			return (set_error(philo->datas, LOCK_MUTEX_ERROR));
		philo->datas->dead = TRUE;
		if (pthread_mutex_unlock(&(philo->datas->end_m)))
			return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
		return (0);
	}
	if (pthread_mutex_unlock(&(philo->datas->fork_m[philo->forkL])))
		return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
	if (pthread_mutex_unlock(&(philo->datas->fork_m[philo->forkR])))
		return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
	if (message(philo, "is sleeping\n", "\033[0;33m"))
		return (-1);
	my_sleep(philo->datas->sleep_time);
	return (0);
}

int	eat(t_philo *philo)
{
	long	time;

	time = 0;
	if (philo->datas->dead || philo->datas->is_end)
	{
		pthread_mutex_lock(&(philo->datas->end_m));
		philo->datas->dead = TRUE;
		pthread_mutex_unlock(&(philo->datas->end_m));
		return (0);
	}
	if (pthread_mutex_lock(&(philo->datas->eat_m)))
		return (set_error(philo->datas, LOCK_MUTEX_ERROR));
	time = ft_get_time();
	if (time == -1)
		return (set_error(philo->datas, TIME_ERROR));
	pthread_mutex_lock(&(philo->datas->end_m));
	philo->start_eat_time = time;
	pthread_mutex_unlock(&(philo->datas->end_m));
	philo->datas->eat_count++;
	if (message(philo, "is eating\n", "\033[0;32m"))
		return (-1);
	if (pthread_mutex_unlock(&(philo->datas->eat_m)))
		return (set_error(philo->datas, UNLOCK_MUTEX_ERROR));
	my_sleep(philo->datas->eat_time);
	return (0);
}
