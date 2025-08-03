/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:10 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:38:53 by akwadran         ###   ########.fr       */
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

typedef enum e_state
{
	HUNGRY,
	FULL,
	DEAD
}	t_state;

typedef struct	s_philosopher
{
	int			index;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	long long		last_meal;
	pthread_t		th;
	struct s_data		*data;
	t_state			state;
	int			nb_of_meals;
} t_philosopher;

typedef struct	s_data
{
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	long long		start_time;
	t_philosopher		*philos;
	pthread_mutex_t		*forks;
	pthread_t		watch;
	int			count;
} t_data;

// main.c
int		create_threads(t_data *data);

// validator.c
bool		valid_arguments(int argc, char **argv);
bool		valid_number_of_args(int argc);
bool		are_args_digits(char **argv);
bool		are_args_positive(char **argv);

// utils.c
int		ft_atoi(const char *nptr);
int		ft_isspace(int c);
int		ft_isdigit(int c);

// data.c
int		init_data(t_data *data, int argc, char **argv);
void		init_parameters(t_data *data, int argc, char **argv);
int		allocate_memory(t_data *data);
void		finish_program(t_data *data);
void		free_memory(t_data *data);

// time.c
long long	get_timestamp(void);
long long	elapsed_time(long long start_time);
void		print_state(t_philosopher *philo, char *msg);

// forks.c
int		init_forks(t_data *data);
int		grab_fork(t_philosopher *philo, pthread_mutex_t *fork);
void		drop_fork(pthread_mutex_t *fork);
void		drop_forks(t_philosopher *philo);
void		destroy_forks(t_data *data);

// philos.c
int		init_philosophers(t_data *data, t_philosopher *philo);
int		create_philos(t_data *data, t_philosopher *philo, int odd);
int		join_threads(t_data *data, t_philosopher *philo);

// watch.c
void		*watch_for_dead(void *arg);
bool		has_died(t_philosopher *philo, long long time_to_die);

// routine.c
void		*routine(void *arg);
int		eating(t_philosopher *philo);
int		sleeping(t_philosopher *philo);
int		thinking(t_philosopher *philo);

// aux.c
void		print_data(t_data *data);
void		print_philos_data(t_data *data, t_philosopher *philo);

#endif
