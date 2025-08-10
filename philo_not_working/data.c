/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:51:12 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:28:59 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	init_parameters(data, argc, argv);
	if (allocate_memory(data) > 0)
	{
		printf("malloc error\n");
		return (1);
	}
	if (init_forks(data) > 0)
	{
		printf("mutex init error");
		free_memory(data);
		return (2);
	}
	if (init_philosophers(data, data->philos) > 0)
	{
		printf("philo mutex init error");
		destroy_forks(data);
		free_memory(data);
		return (3);
	}
	if (init_data_mutexes(data) > 0)
	{
		printf("data mutex init error");
		destroy_forks(data);
		destroy_mutexes(data, data->philos);
		free_memory(data);
		return (3);
	}
	//data->start_time = get_timestamp();
	return (0);
}

void	init_parameters(t_data *data, int argc, char **argv)
{
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	data->start_time = LLONG_MIN;
	//data->count = 0;
	data->full_philos = 0;
	data->start = false;
	data->finish = false;
}

int	allocate_memory(t_data *data)
{
	data->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * data->number_of_philosophers);
	if (!data->philos)
		return (1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!data->forks)
	{
		free(data->philos);
		data->philos = NULL;
		return (1);
	}
	return (0);
}

int	init_data_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->start_mutex, NULL) > 0)
		return (1);
	if (pthread_mutex_init(&data->finish_mutex, NULL) > 0)
		return (1);
	if (pthread_mutex_init(&data->full_mutex, NULL) > 0)
		return (1);
	return (0);
}

void	finish_program(t_data *data)
{
	join_threads(data, data->philos);
	destroy_forks(data);
	destroy_mutexes(data, data->philos);
	destroy_data_mutexes(data);
	free_memory(data);
}

void	free_memory(t_data *data)
{
	free(data->philos);
	data->philos = NULL;
	free(data->forks);
	data->forks = NULL;
}

void	destroy_data_mutexes(t_data *data)
{
	pthread_mutex_destroy(&data->start_mutex);
	pthread_mutex_destroy(&data->finish_mutex);
	pthread_mutex_destroy(&data->full_mutex);
}
