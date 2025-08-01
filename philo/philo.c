/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 15:18:04 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Argumentos: 
	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]

Funciones autorizadas:
	memset			pthread_create
	printf			pthread_detach
	malloc			pthread_join
	free			pthread_mutex_init
	write			pthread_mutex_destroy
	usleep			pthread_mutex_lock
	gettimeofday		pthread_mutex_unlock
*/

#include "philo.h"

bool	

bool	valid_arguments(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf()
	}
		return (0);
	
}

int	main(int argc, char **argv)
{
	t_data  data;

	valid_arguments(argc, argv);
	init_data();
	/* routines */
	return (0);
}
