/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:40:36 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 17:43:21 by akwadran         ###   ########.fr       */
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

int	grab_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	if (philo->state == DEAD)
		return (1);
	pthread_mutex_lock(fork);
	if (philo->state == ALIVE)
		print_state(philo, "has taken a fork");
	return (0);
}

void	drop_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	drop_forks(t_philosopher *philo)
{
	drop_fork(philo->right_fork);
	print_state(philo, "has dropped a fork");
	drop_fork(philo->left_fork);
	print_state(philo, "has dropped a fork");
}

void	destroy_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
