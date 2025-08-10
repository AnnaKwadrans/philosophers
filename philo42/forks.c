/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:40:36 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 20:12:47 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) > 0)
			return (1);
		i++;
	}
	return (0);
}

int	grab_forks(t_philosopher *philo)
{
	//pthread_mutex_t	*first;
	//pthread_mutex_t	*second;

	if (has_dinner_finished(philo->data))
		return (1);
	/*
	if (philo->index % 2 == 0)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	*/
	pthread_mutex_lock(philo->first_fork); 
	if (!has_dinner_finished(philo->data))
		print_state(philo, "has taken a fork");
	pthread_mutex_lock(philo->second_fork);
	if (!has_dinner_finished(philo->data))
		print_state(philo, "has taken a fork");
	return (0);
}

void	drop_forks(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}

void	assign_forks(t_data *data, t_philosopher *philo, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		///printf("i: %d, nb philos: %d, index: %d\n", i, data->nb_of_philos, philo[i].index);
		if (philo[i].index % 2 != 0)
		{
			philo[i].first_fork = &forks[i];
			if (i == 0)
				philo[i].second_fork = &forks[data->nb_of_philos - 1];
			else
				philo[i].second_fork = &forks[i - 1];
		}
		else
		{
			philo[i].first_fork = &forks[i - 1];
			philo[i].second_fork = &forks[i];
		}
		i++;
	}
}
