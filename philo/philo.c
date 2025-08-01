/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 17:01:05 by akwadran         ###   ########.fr       */
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



int	main(int argc, char **argv)
{
	t_data  data;

	if (!valid_arguments(argc, argv))
		return (1);
	init_data(&data, argc, argv);
	print_data(&data);
	/* routines */
	return (0);
}
