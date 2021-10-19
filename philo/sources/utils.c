/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwourms <lwourms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:09:10 by lwourms           #+#    #+#             */
/*   Updated: 2021/10/19 20:09:07 by lwourms          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	set_error(t_datas *datas, t_error error)
{
	if (pthread_mutex_lock(&(datas->error_m)))
		return (LOCK_MUTEX_ERROR);
	datas->error_type = error;
	if (pthread_mutex_unlock(&(datas->error_m)))
		return (UNLOCK_MUTEX_ERROR);
	return (error);
}

void	my_sleep(long time_to_wait)
{
	long	time;

	time = ft_get_time();
	while (time + time_to_wait > ft_get_time())
		usleep(50);
}

t_bool	is_digit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
	return (TRUE);
}

long	my_atol(const char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] >= '0' && str[i] <= '9')
		nb = (nb * 10) + (str[i++] - '0');
	return (nb);
}

long	ft_get_time(void)
{
	struct timeval	current;

	if (gettimeofday(&current, NULL))
		return (-1);
	return (current.tv_sec * 1000 + current.tv_usec / 1000);
}
