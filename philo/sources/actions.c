/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:24:48 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/17 18:02:41 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	message(t_philo *philo, const char *msg, const char *color)
{
	long	time;

	time = 0;
	if (philo->datas->dead || philo->datas->is_end)
	{
		if (pthread_mutex_lock(&(philo->datas->write_m)))
			return (philo->datas->error_type = LOCK_MUTEX_ERROR);
		return (0);
	}
	if (pthread_mutex_lock(&(philo->datas->write_m)))
		return (philo->datas->error_type = LOCK_MUTEX_ERROR);
	time = ft_get_time();
	time = time - philo->datas->start_time_simul;
	printf("%.5ld %s%d %s\033[0m", time, color, philo->id + 1, msg);
	if (pthread_mutex_unlock(&(philo->datas->write_m)))
		return (philo->datas->error_type = UNLOCK_MUTEX_ERROR);
	return (0);
}

int	think(t_philo *philo)
{
	if (philo->datas->dead || philo->datas->is_end)
		return (0);
	if (message(philo, "is thinking\n", "\033[0;35m"))
		return (1);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->datas->dead || philo->datas->is_end)
		return (0);
	if (pthread_mutex_lock(&(philo->datas->fork_m[philo->forkL])))
		return (philo->datas->error_type = LOCK_MUTEX_ERROR);
	if (pthread_mutex_lock(&(philo->datas->fork_m[philo->forkR])))
		return (philo->datas->error_type = LOCK_MUTEX_ERROR);
	if (message(philo, "has taken a fork\n", "\033[0;36m"))
		return (philo->datas->error_type);
	if (message(philo, "has taken a fork\n", "\033[0;36m"))
		return (philo->datas->error_type);
	return (0);
}

int	drop_forks_n_sleep(t_philo *philo)
{
	long	time;

	time = 0;
	if (philo->datas->dead || philo->datas->is_end)
		return (0);
	if (pthread_mutex_unlock(&(philo->datas->fork_m[philo->forkL])))
		return (1);
	if (pthread_mutex_unlock(&(philo->datas->fork_m[philo->forkR])))
		return (1);
	if (message(philo, "is sleeping\n", "\033[0;33m"))
		return (1);
	my_sleep(philo->datas->sleep_time);
	return (0);
}

int	eat(t_philo *philo)
{
	long	time;

	time = 0;
	if (philo->datas->dead || philo->datas->is_end)
		return (0);
	if (pthread_mutex_lock(&(philo->datas->eat_m)))
		return (philo->datas->error_type = LOCK_MUTEX_ERROR);
	time = ft_get_time();
	if (time == -1)
		return (philo->datas->error_type = TIME_ERROR);
	philo->start_eat_time = time;
	philo->datas->eat_count++;
	if (message(philo, "is eating\n", "\033[0;32m"))
		return (philo->datas->error_type);
	if (pthread_mutex_unlock(&(philo->datas->eat_m)))
		return (philo->datas->error_type = UNLOCK_MUTEX_ERROR);
	my_sleep(philo->datas->eat_time);
	return (0);
}
