/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:39:22 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:37:36 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch(void *arg)
{
	t_data		*data;
	t_philosopher 	*philo;
	int		i;

	data = (t_data *)arg;
	philo = data->philos;
	//all_ths_created(data);
	while (!has_dinner_finished(data) && !are_philos_full(data))
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (check_state(&philo[i], HUNGRY) && has_died(&philo[i], data->time_to_die))
			{
				change_state(&philo[i], DEAD);
				pthread_mutex_lock(&data->finish_mutex);
				data->finish = true;
				pthread_mutex_unlock(&data->finish_mutex);
				print_state(&philo[i], "died");
				break ;
			}
			i++;
		}
	}
	printf("WATCH ENDED\n");
	return (NULL);
	//usleep(data->time_to_die * 1000 - 1000);
	/*
	while (data->count < data->number_of_philosophers)
	{
		//printf("count: %d\n", data->count);
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&philo[i].state_mutex);
			if (philo[i].state == FULL)
				data->count++;
			else if (philo[i].state == HUNGRY && has_died(&philo[i], data->time_to_die))
			{
				data->count++;
				philo[i].state = DEAD;
				print_state(&philo[i], "died");
			}
			pthread_mutex_unlock(&philo[i].state_mutex);
			i++;
		}
	}
	return (NULL);
	*/
}

int	get_full_philos_nb(t_data *data)
{
	int	full_philos;

	pthread_mutex_lock(&data->full_mutex);
	full_philos = data->full_philos;
	pthread_mutex_unlock(&data->full_mutex);
	return (full_philos);
}

bool	are_philos_full(t_data *data)
{
	int	full_philos;

	full_philos = get_full_philos_nb(data);
	if (full_philos >= data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->finish_mutex);
		data->finish = true;
		pthread_mutex_unlock(&data->finish_mutex);
		printf("PHILOS FULL\n");
		return (1);
	}
	/*else
		printf("PHILOS >>>NOT<<< FULL\n");*/
	return (0);
}

bool	has_died(t_philosopher *philo, long long time_to_die)
{
	long long	ts;
	//long long	lm;
	long long	diff;
	
	ts = elapsed_time(philo->data->start_time);
	pthread_mutex_lock(&philo->last_meal_mutex);
	diff = ts - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (diff > time_to_die)
		return (1);
	return (0);
}
