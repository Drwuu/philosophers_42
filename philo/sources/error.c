/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:09:10 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/19 20:22:25 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static char	*get_error_type_2(t_error error)
{
	if (error == PRINTF_ERROR)
		return ("PRINTF_ERROR");
	else if (error == TIME_ERROR)
		return ("TIME_ERROR");
	else if (error == ARGUMENTS_ERROR)
		return ("ARGUMENTS_ERROR");
	else if (error == ARGUMENTS_DIGIT_ERROR)
		return ("ARGUMENTS_DIGIT_ERROR");
	else if (error == MALLOC_ERROR)
		return ("MALLOC_ERROR");
	else if (error == USLEEP_ERROR)
		return ("USLEEP_ERROR");
	else
		return (NULL);
}

char	*get_error_type(t_error error)
{
	if (error == INIT_MUTEX_ERROR)
		return ("INIT_MUTEX_ERROR");
	else if (error == LOCK_MUTEX_ERROR)
		return ("LOCK_MUTEX_ERROR");
	else if (error == UNLOCK_MUTEX_ERROR)
		return ("UNLOCK_MUTEX_ERROR");
	else if (error == DESTROY_MUTEX_ERROR)
		return ("DESTROY_MUTEX_ERROR");
	else if (error == THREAD_CREATE_ERROR)
		return ("THREAD_CREATE_ERROR");
	else if (error == THREAD_DETACH_ERROR)
		return ("THREAD_DETACH_ERROR");
	else if (error == THREAD_JOIN_ERROR)
		return ("THREAD_JOIN_ERROR");
	return (get_error_type_2(error));
}

static char	*message_error_2(t_error error)
{
	if (error == THREAD_DETACH_ERROR)
		return ("Thread detach failed");
	else if (error == THREAD_JOIN_ERROR)
		return ("Thread join failed");
	else if (error == PRINTF_ERROR)
		return ("Printf failed");
	else if (error == TIME_ERROR)
		return ("Getting time failed");
	else if (error == ARGUMENTS_ERROR)
		return ("Usage: number_of_philosophers time_to_die " \
			"time_to_eat time_to_sleep " \
			"[number_of_times_each_philosopher_must_eat]");
	else if (error == ARGUMENTS_DIGIT_ERROR)
		return ("Please use positive numbers");
	else if (error == MALLOC_ERROR)
		return ("Malloc broke up");
	else if (error == USLEEP_ERROR)
		return ("Usleep failed");
	else
		return (NULL);
}

char	*message_error(t_error error)
{
	if (error == INIT_MUTEX_ERROR)
		return ("Mutex initialization failed");
	else if (error == LOCK_MUTEX_ERROR)
		return ("Mutex lock failed");
	else if (error == UNLOCK_MUTEX_ERROR)
		return ("Mutex unlock failed");
	else if (error == DESTROY_MUTEX_ERROR)
		return ("Mutex destroy failed");
	else if (error == THREAD_CREATE_ERROR)
		return ("Thread create failed");
	else
		return (message_error_2(error));
}

int	error_manager(t_datas *datas, t_philo *philos, t_error error)
{
	if (error != NO_ERROR)
		printf("Error of type %s:\n%s\n", get_error_type(error), \
			message_error(error));
	clear_datas(philos, datas);
	return (-1);
}
