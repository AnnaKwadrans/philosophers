/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:51:12 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 20:18:57 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		printf("fork %d: %p\n", i + 1, &data->forks[i]);
		//printf("lm: %p, state: %p\n", &philo[i].last_meal_mutex, &philo[i].state_mutex);
		i++;
	}
	//printf("ts: %lld\n", get_timestamp());
}

void	print_philos_data(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		printf("%d - first: %p, second: %p\n", philo[i].index, philo[i].first_fork, philo[i].second_fork);
		//printf("lm: %p, state: %p\n", &philo[i].last_meal_mutex, &philo[i].state_mutex);
		i++;
	}
	//printf("ts: %lld\n", get_timestamp());
}

int	init_data(t_data *data, int argc, char **argv)
{
	init_parameters(data, argc, argv);
	if (allocate_memory(data) > 0)
	{
		printf("malloc error\n");
		return (1);
	}
	if (init_data_mutexes(data) > 0)
	{
		printf("mutex init error");
		free_memory(data);
		return (2);
	}
	if (init_philosophers(data, data->philos) > 0)
	{
		printf("philo mutex init error");
		destroy_data_mutexes(data);
		free_memory(data);
		return (3);
	}
	assign_forks(data, data->philos, data->forks);
	//print_forks(data);
	//print_philos_data(data, data->philos);
	return (0);
}

void	init_parameters(t_data *data, int argc, char **argv)
{
	data->nb_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_each_philosopher_must_eat = -1;
	data->start_time = LLONG_MIN;
	data->full_philos = 0;
	data->finish = false;
}

int	allocate_memory(t_data *data)
{
	data->philos = (t_philosopher *)malloc(sizeof(t_philosopher)
			* data->nb_of_philos);
	if (!data->philos)
		return (1);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->nb_of_philos);
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
	if (init_forks(data) > 0)
		return (1);
	if (pthread_mutex_init(&data->finish_mutex, NULL) > 0)
		return (1);
	if (pthread_mutex_init(&data->full_mutex, NULL) > 0)
		return (1);
	if (pthread_mutex_init(&data->stdout_mutex, NULL) > 0)
		return (1);
	return (0);
}
