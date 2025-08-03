/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:46:14 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 17:54:17 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print_philos_data(t_data *data, t_philosopher *philo)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		printf("%d - left: %p, right: %p\n", philo[i].index, philo[i].left_fork, philo[i].right_fork);
		i++;
		printf("ts: %lld\n", get_timestamp());
	}
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
