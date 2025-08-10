/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:02 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 20:23:33 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (!valid_arguments(argc, argv))
		return (1);
	if (init_data(&data, argc, argv) > 0)
		return (2);
	if (create_threads(&data) > 0)
		return (3);
	finish_program(&data);
	return (0);
}

int	create_threads(t_data *data)
{
	record_start_time(data, data->philos);
	if (create_philos(data, data->philos, 0) > 0)
		return (1);
	if (create_philos(data, data->philos, 1) > 0)
		return (2);
	if (pthread_create(&data->watch, NULL, &watch, data) > 0)
	{
		printf("create watch thread error\n");
		return (2);
	}
	return (0);
}

void	record_start_time(t_data *data, t_philosopher *philos)
{
	int	i;

	data->start_time = get_timestamp();
	i = 0;
	while (i < data->nb_of_philos)
	{
		philos[i].start_time = data->start_time;
		i++;
	}
}

void	one_philo(t_data *data)
{
	data->start_time = get_timestamp();
	printf("%lld 1 has taken a fork\n", elapsed_time(data->start_time));
	while (1)
	{
		if (elapsed_time(data->start_time) >= data->time_to_die)
			break ;
	}
	printf("%lld 1 diead\n", elapsed_time(data->start_time));
}
