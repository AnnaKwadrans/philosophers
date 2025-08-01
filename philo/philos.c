/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:52:50 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 21:55:02 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) > 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philosophers(t_data *data, t_philosopher *philo)
{
	int	i;
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].index = i;
		philo[i].right_fork = &data->forks[i];
		if (i == data->number_of_philosophers - 1)
			philo[i].left_fork = &data->forks[0];
		else
			philo[i].left_fork = &data->forks[i + 1];
		philo[i].last_meal = 0;
		philo[i].data = data;
		i++;
	}
	return (0);
}

int	create_threads(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].th, NULL, &routine, philo) > 0)
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].th, NULL) > 0)
			return (1);
		i++;
	}
	return (0);
}
