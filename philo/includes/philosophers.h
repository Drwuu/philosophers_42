#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_error
{
	NO_ERROR = 0,
	INIT_MUTEX_ERROR = 10,
	LOCK_MUTEX_ERROR,
	UNLOCK_MUTEX_ERROR,
	DESTROY_MUTEX_ERROR,
	THREAD_CREATE_ERROR,
	THREAD_DETACH_ERROR,
	THREAD_JOIN_ERROR,
	PRINTF_ERROR,
	TIME_ERROR,
	ARGUMENTS_ERROR,
	ARGUMENTS_DIGIT_ERROR,
	MALLOC_ERROR,
	USLEEP_ERROR
}	t_error;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_datas
{
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	end_m;
	pthread_mutex_t	eat_m;
	pthread_mutex_t	write_m;
	pthread_mutex_t	error_m;
	pthread_t		monitor_thread;

	t_error			error_type;

	int				philo_nb;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	int				must_eat_count;
	int				eat_count;
	long			start_time_simul;
}	t_datas;

typedef struct s_philo
{
	t_datas		*datas;
	pthread_t	thread;

	int			id;
	int			forkL;
	int			forkR;
	long		start_eat_time;
}	t_philo;

/* check_status.c */
void	*monitor(void *philos);

/* actions.c */
int		message(t_philo *philo, const char *msg, const char *color);
int		take_forks(t_philo *philo);
int		eat(t_philo *philo);
int		drop_forks_n_sleep(t_philo *philo);
int		think(t_philo *philo);

/* init.c */
int		init_datas(int ac, char **av, t_datas *datas);

/* utils.c */
int		set_error(t_datas *datas, t_error error);
t_bool	is_digit(char *str);
long	my_atol(const char *str);
long	ft_get_time(void);
void	my_sleep(long time_to_wait);

/* error.c */
int		error_manager(t_datas *datas, t_philo *philos, t_error error);
char	*get_error_type(t_error error);
char	*message_error(t_error error);

/* clear.c */
void	clear_datas(t_philo *philos, t_datas *datas);
int		destroy_mutexes(t_datas *datas);

#endif
