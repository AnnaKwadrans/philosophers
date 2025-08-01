/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:10 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 21:50:35 by akwadran         ###   ########.fr       */
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

typedef struct s_fork
{
	int	index;
	pthread_mutex_t	*fork;
	struct s_fork	*next;
}	t_fork;

typedef struct	s_philosopher
{
	int			index;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	long long		last_meal;
	pthread_t		th;
	struct s_data		*data;




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


} t_data;



// validator.c
bool	valid_arguments(int argc, char **argv);
bool	valid_number_of_args(int argc);
bool	are_args_valid_numbers(char **argv);

// data.c
void		init_data(t_data *data, int argc, char **argv);
void		init_parameters(t_data *data, int argc, char **argv);
void		print_data(t_data *data); // auxiliar
long long	get_timestamp(void);
long long	elapsed_time(long long start_time);

// utils.c
int	ft_atoi(const char *nptr);
int	ft_isspace(int c);
int	ft_isdigit(int c);

// philos.c
int	init_forks(t_data *data);
int	init_philosophers(t_data *data, t_philosopher *philo);
int	create_threads(t_data *data, t_philosopher *philo);
int	join_threads(t_data *data, t_philosopher *philo);

// routine.c
void	*routine(void *arg);


#endif