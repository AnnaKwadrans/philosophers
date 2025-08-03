/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:39:22 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 18:16:43 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watch_for_dead(void *arg)
{
	t_data		*data;
	t_philosopher 	*philo;
	int		i;

	data = (t_data *)arg;
	philo = data->philos;
	while (data->count < data->number_of_philosophers)
	{
		//printf("count: %d\n", data->count);
		i = 0;
		while (i < data->number_of_philosophers)
		{
			if (philo[i].state == FULL)
				data->count++;
			else if (philo[i].state == ALIVE && has_died(&philo[i], data->time_to_die))
			{
				philo[i].state = DEAD;
				data->count++;
				print_state(&philo[i], "died");
			}
			i++;
		}
	}
	return (NULL);
}

bool	has_died(t_philosopher *philo, long long time_to_die)
{
	long long	ts;
	long long	lm;
	long long	diff;
	
	ts = elapsed_time(philo->data->start_time);
	diff = ts - philo->last_meal;
	//printf("DEATH ts: %lld, lm: %lld, diff: %lld\n", ts, philo->last_meal, diff);
	//if ((get_timestamp() - philo->last_meal) > time_to_die)
	if (diff > time_to_die)
		return (1);
	return (0);
}
