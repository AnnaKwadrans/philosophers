/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:10 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 19:59:47 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_philosopher
{
	int				index;
	pthread_t		th;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;
	long long		last_meal;
	int				nb_of_meals;
	pthread_mutex_t	last_meal_mutex;
	struct s_data	*data;
	int				max_meals;
	long long		start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_philos;
	pthread_mutex_t	*stdout_mutex;
}	t_philosopher;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	long long		start_time;
	t_philosopher	*philos;
	pthread_mutex_t	*forks;
	pthread_t		watch;
	int				full_philos;
	pthread_mutex_t	full_mutex;
	bool			finish;
	pthread_mutex_t	finish_mutex;
	pthread_mutex_t	stdout_mutex;
}	t_data;

// main.c
int			create_threads(t_data *data);
void		record_start_time(t_data *data, t_philosopher *philos);

// validator.c
bool		valid_arguments(int argc, char **argv);
bool		valid_number_of_args(int argc);
bool		are_args_digits(char **argv);
bool		are_args_positive(char **argv);
bool		args_within_limit(char **argv);

// utils.c
int			ft_atoi(const char *nptr);
int			ft_isspace(int c);
int			ft_isdigit(int c);
bool		atoi_limit_checker(const char *nptr);

// data.c
int			init_data(t_data *data, int argc, char **argv);
void		init_parameters(t_data *data, int argc, char **argv);
int			allocate_memory(t_data *data);
int			init_data_mutexes(t_data *data);

// time.c
long long	get_timestamp(void);
long long	elapsed_time(long long start_time);
void		print_state(t_philosopher *philo, char *msg);
void		ft_usleep(long long time);

// forks.c
int			init_forks(t_data *data);
int			grab_forks(t_philosopher *philo);
void		drop_forks(t_philosopher *philo);
void		destroy_forks(t_data *data);
void		assign_forks(t_data *data, t_philosopher *philo, pthread_mutex_t *forks);

// philos.c
int			init_philosophers(t_data *data, t_philosopher *philo);
int			create_philos(t_data *data, t_philosopher *philo, int odd);
int			init_philo_mutexes(t_philosopher *philo);
void		destroy_philos_mutexes(t_data *data, t_philosopher *philos);
int			join_threads(t_data *data, t_philosopher *philo);

// watch.c
void		*watch(void *arg);
bool		are_philos_full(t_data *data);
bool		has_died(t_philosopher *philo, long long time_to_die);
bool		has_dinner_finished(t_data *data);

// routine.c
void		record_full_philo(t_philosopher *philo);
void		*routine(void *arg);
int			eating(t_philosopher *philo);
int			sleeping(t_philosopher *philo);
int			thinking(t_philosopher *philo);

// cleanup.c
void		finish_program(t_data *data);
void		destroy_data_mutexes(t_data *data);
void		free_memory(t_data *data);

#endif
