/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:52:50 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 20:27:58 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philosophers(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		philo[i].index = i + 1;
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].nb_of_meals = 0;
		philo[i].max_meals = data->number_of_times_each_philosopher_must_eat;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		philo[i].nb_of_philos = data->nb_of_philos;
		philo[i].stdout_mutex = &philo->data->stdout_mutex;
		if (init_philo_mutexes(&philo[i]) > 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philo_mutexes(t_philosopher *philo)
{
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL) > 0)
		return (1);
	return (0);
}

void	destroy_philos_mutexes(t_data *data, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		i++;
	}
}

int	create_philos(t_data *data, t_philosopher *philo, int odd)
{
	int	i;

	i = odd;
	while (i < data->nb_of_philos)
	{
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) > 0)
		{
			printf("create philo thread error\n");
			return (1);
		}
		//usleep(10);
		i += 2;
	}
	return (0);
}

int	join_threads(t_data *data, t_philosopher *philo)
{
	int	i;

	pthread_join(data->watch, NULL);
	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_join(philo[i].th, NULL) > 0)
			return (1);
		i++;
	}
	return (0);
}
