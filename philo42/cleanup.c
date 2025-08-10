/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 17:35:22 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 18:35:20 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	finish_program(t_data *data)
{
	join_threads(data, data->philos);
	destroy_philos_mutexes(data, data->philos);
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
	destroy_forks(data);
	pthread_mutex_destroy(&data->finish_mutex);
	pthread_mutex_destroy(&data->full_mutex);
	pthread_mutex_destroy(&data->stdout_mutex);
}
