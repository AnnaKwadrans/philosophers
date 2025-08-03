/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:52:50 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:38:09 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		philo[i].state = HUNGRY;
		philo[i].nb_of_meals = 0;
		i++;
	}
	return (0);
}

int	create_philos(t_data *data, t_philosopher *philo, int odd)
{
	int	i;

	i = odd;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) > 0)
		{
			printf("create philo thread error\n");
			return (1);
		}
		i += 2;
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
