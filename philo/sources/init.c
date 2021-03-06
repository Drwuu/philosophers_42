/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:48:31 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/20 13:33:48 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*init_mutex_array(t_datas *datas, int nb)
{
	pthread_mutex_t	*array;
	int				i;

	array = malloc(sizeof(*array) * nb);
	if (!array)
	{
		datas->error_type = MALLOC_ERROR;
		return (NULL);
	}
	i = -1;
	while (++i < nb)
	{
		if (pthread_mutex_init(&(array[i]), NULL))
		{
			datas->error_type = INIT_MUTEX_ERROR;
			return (NULL);
		}
	}
	return (array);
}

static int	prepare_datas(t_datas *datas, char **av)
{
	datas->error_type = NO_ERROR;
	datas->start_time_simul = 0;
	datas->eat_count = 0;
	datas->philo_nb = my_atol(av[1]);
	datas->die_time = my_atol(av[2]);
	datas->eat_time = my_atol(av[3]);
	datas->sleep_time = my_atol(av[4]);
	if (datas->philo_nb > 200 || datas->die_time > 2147483647 || \
	datas->eat_time > 2147483647 || datas->sleep_time > 2147483647)
		return (datas->error_type = ARGUMENTS_LIMIT_ERROR);
	if (av[5])
	{
		datas->must_eat_count = my_atol(av[5]);
		if (datas->must_eat_count > 2147483647)
			return (datas->error_type = ARGUMENTS_LIMIT_ERROR);
	}
	datas->fork_m = init_mutex_array(datas, datas->philo_nb);
	if (!(datas->fork_m))
		return (datas->error_type);
	return (0);
}

int	init_datas(int ac, char **av, t_datas *datas)
{
	if (ac < 5 || ac > 6)
		return (datas->error_type = ARGUMENTS_ERROR);
	if (!is_digit(av[1]) || !is_digit(av[2]) || !is_digit(av[3]) || \
	!is_digit(av[4]))
		return (datas->error_type = ARGUMENTS_DIGIT_ERROR);
	if (av[5] && !is_digit(av[5]))
		return (datas->error_type = ARGUMENTS_DIGIT_ERROR);
	if (prepare_datas(datas, av))
		return (datas->error_type);
	if (pthread_mutex_init(&(datas->eat_m), NULL) || \
		pthread_mutex_init(&(datas->write_m), NULL) || \
		pthread_mutex_init(&(datas->end_m), NULL))
		return (datas->error_type = INIT_MUTEX_ERROR);
	return (0);
}
