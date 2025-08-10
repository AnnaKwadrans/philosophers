/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:39:22 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 17:06:24 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch(void *arg)
{
	t_data			*data;
	t_philosopher	*philo;
	int				i;

	data = (t_data *)arg;
	philo = data->philos;
	while (!has_dinner_finished(data) && !are_philos_full(data))
	{
		i = 0;
		while (i < data->nb_of_philos)
		{
			if (has_died(&philo[i], data->time_to_die))
			{
				pthread_mutex_lock(&data->finish_mutex);
				data->finish = true;
				pthread_mutex_unlock(&data->finish_mutex);
				print_state(&philo[i], "died");
				break ;
			}
			i++;
		}
	}
	return (NULL);
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
	if (full_philos >= data->nb_of_philos)
	{
		pthread_mutex_lock(&data->finish_mutex);
		data->finish = true;
		pthread_mutex_unlock(&data->finish_mutex);
		return (1);
	}
	return (0);
}

bool	has_died(t_philosopher *philo, long long time_to_die)
{
	long long	ts;
	long long	diff;

	ts = elapsed_time(philo->data->start_time);
	pthread_mutex_lock(&philo->last_meal_mutex);
	diff = ts - philo->last_meal;
	pthread_mutex_unlock(&philo->last_meal_mutex);
	if (diff > time_to_die)
		return (1);
	return (0);
}

bool	has_dinner_finished(t_data *data)
{
	bool	finish;

	pthread_mutex_lock(&data->finish_mutex);
	finish = data->finish;
	pthread_mutex_unlock(&data->finish_mutex);
	return (finish);
}
