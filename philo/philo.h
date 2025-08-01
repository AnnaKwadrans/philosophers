/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:10 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 17:01:29 by akwadran         ###   ########.fr       */
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

typedef struct	t_data
{
	int	number_of_pfilosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;


} t_data;

typedef struct	s_philosopher
{
	
} t_philosopher;

// validator.c
bool	valid_arguments(int argc, char **argv);
bool	valid_number_of_args(int argc);
bool	are_args_valid_numbers(char **argv);

// data.c
void	init_data(t_data *data, int argc, char **argv);
void	print_data(t_data *data); // auxiliar

// utils.c
int	ft_atoi(const char *nptr);
int	ft_isspace(int c);
int	ft_isdigit(int c);

#endif