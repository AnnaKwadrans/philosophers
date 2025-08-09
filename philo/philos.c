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
		philo[i].index = i + 1;
		philo[i].right_fork = &data->forks[i];
		if (i == data->number_of_philosophers - 1)
			philo[i].left_fork = &data->forks[0];
		else
			philo[i].left_fork = &data->forks[i + 1];
		philo[i].last_meal = 0;
		philo[i].data = data;
		philo[i].state = HUNGRY;
		philo[i].nb_of_meals = 0;
		philo[i].max_meals = data->number_of_times_each_philosopher_must_eat;
		philo[i].time_to_die = data->time_to_die;
		philo[i].time_to_eat = data->time_to_eat;
		philo[i].time_to_sleep = data->time_to_sleep;
		if (init_mutexes(&philo[i]) > 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_mutexes(t_philosopher *philo)
{
	if (pthread_mutex_init(&philo->state_mutex, NULL) > 0)
		return (1);
	if (pthread_mutex_init(&philo->last_meal_mutex, NULL) > 0)
		return (1);
	return (0);
}

void	destroy_philos_mutexes(t_data *data, t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos[i].last_meal_mutex);
		pthread_mutex_destroy(&philos[i].state_mutex);
		i++;
	}
}

int	create_philos(t_data *data, t_philosopher *philo, int odd)
{
	int	i;

	i = odd; // remove
	//i = 0;
	//data->start_time = get_timestamp();
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].th, NULL, &routine, &philo[i]) > 0)
		{
			printf("create philo thread error\n");
			return (1);
		}
		i++;
		//i += 2;
	}
	return (0);
}

int	join_threads(t_data *data, t_philosopher *philo)
{
	int	i;

	pthread_join(data->watch, NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].th, NULL) > 0)
			return (1);
		i++;
	}
	return (0);
}

bool	check_state(t_philosopher *philo, t_state state_to_check)
{
	bool	ret;
	
	ret = false;
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == state_to_check)
		ret = true;
	pthread_mutex_unlock(&philo->state_mutex);
	return (ret);
}

void	change_state(t_philosopher *philo, t_state new_state)
{
	pthread_mutex_lock(&philo->state_mutex);
	philo->state = new_state;
	pthread_mutex_unlock(&philo->state_mutex);
}