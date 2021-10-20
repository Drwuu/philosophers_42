/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:15:24 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/20 13:19:45 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_philo	*create_philos(t_datas *datas)
{
	t_philo	*philos;
	long	time;
	int		i;

	i = -1;
	time = 0;
	philos = malloc(sizeof(*philos) * datas->philo_nb);
	if (!philos)
	{
		datas->error_type = MALLOC_ERROR;
		return (NULL);
	}
	while (++i < datas->philo_nb)
	{
		time = ft_get_time();
		philos[i].datas = datas;
		philos[i].id = i;
		philos[i].start_eat_time = time;
		philos[i].forkL = philos[i].id;
		philos[i].forkR = (philos[i].id + 1) % datas->philo_nb;
	}
	return (philos);
}

static void	*routine(void *philo_p)
{
	t_philo	*philo;

	philo = (t_philo *)philo_p;
	while (TRUE)
	{
		if (take_forks(philo))
			return ((void *)1);
		if (eat(philo))
			return ((void *)1);
		if (drop_forks_n_sleep(philo))
			return ((void *)1);
		if (think(philo))
			return ((void *)1);
	}
	return (NULL);
}

static int	start_threads(t_philo *philos)
{
	int	i;

	i = -1;
	philos->datas->start_time_simul = ft_get_time();
	if (pthread_create(&philos->datas->monitor_thread, NULL, &monitor, philos))
		return (philos->datas->error_type = THREAD_CREATE_ERROR);
	while (++i < philos->datas->philo_nb)
	{
		if (pthread_create(&(philos[i].thread), NULL, &routine, &(philos[i])))
			return (set_error(philos->datas, THREAD_CREATE_ERROR));
		if (pthread_detach(philos[i].thread))
			return (set_error(philos->datas, THREAD_DETACH_ERROR));
		usleep(100);
	}
	if (pthread_join(philos->datas->monitor_thread, NULL))
		return (set_error(philos->datas, THREAD_JOIN_ERROR));
	return (0);
}

int	main(int ac, char **av)
{
	t_datas		*datas;
	t_philo		*philos;

	philos = NULL;
	datas = malloc(sizeof(*datas));
	if (!datas)
		return (-1);
	if (init_datas(ac, av, datas))
		return (error_manager(datas, philos, datas->error_type));
	philos = create_philos(datas);
	if (!philos)
		return (error_manager(datas, philos, datas->error_type));
	if (start_threads(philos))
		return (error_manager(datas, philos, datas->error_type));
	if (datas->error_type != NO_ERROR)
		return (error_manager(datas, philos, datas->error_type));
	clear_datas(philos, datas);
	return (printf("End of Simulation\n"));
}
