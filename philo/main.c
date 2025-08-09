/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:26:09 by akwadran         ###   ########.fr       */
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
	if (init_data(&data, argc, argv) > 0)
		return (2);
	print_data(&data);
	print_philos_data(&data, data.philos);
    //data.start_time = get_timestamp();
	if (create_threads(&data) > 0)
		return (3);
	printf("TIME ELAPSED FROM START: %lld\n", elapsed_time(data.start_time));
	finish_program(&data);
	return (0);
}

int	create_threads(t_data *data)
{
	if (create_philos(data, data->philos, 0) > 0)
		return (1);
	//if (create_philos(data, data->philos, 2) > 0)
	//	return (2);
    if (pthread_create(&data->watch, NULL, &watch, data) > 0)
	{
		printf("create watch thread error\n");
		return (2);
	}
	record_start_time(data, data->philos);
	pthread_mutex_lock(&data->start_mutex);
	data->start = true;
	pthread_mutex_unlock(&data->start_mutex);
	return (0);
}

void	record_start_time(t_data *data, t_philosopher *philos)
{
	int	i;

	data->start_time = get_timestamp();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].start_time = data->start_time;
		i++;
	}
}