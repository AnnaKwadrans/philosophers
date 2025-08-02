/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:51:12 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 22:53:03 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	data->start_time = get_timestamp();
	data->count = 0;
}

void	init_data(t_data *data, int argc, char **argv)
{
	init_parameters(data, argc, argv);
	allocate_memory(data);
	init_forks(data);
	init_philosophers(data, data->philos);
}

void	print_data(t_data *data)
{
	printf("number_of_pfilosophers: %d\n", data->number_of_philosophers);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("number_of_times_each_philosopher_must_eat: %d\n",
		data->number_of_times_each_philosopher_must_eat);
	printf("start_time: %lld\n", data->start_time);
}
long long	get_timestamp(void)
{
	struct timeval	ts;
	
	if (gettimeofday(&ts, NULL) < 0)
	{
		printf("error retrieving timestamp\n");
		return (-1);
	}
	return ((ts.tv_sec * 1000) + (ts.tv_usec / 1000));
}

long long	elapsed_time(long long start_time)
{
	return (get_timestamp() - start_time);	
}
