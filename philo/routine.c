/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:35:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 21:37:25 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(philo->left_fork);
	printf("%lld %d has taken a fork\n", elapsed_time(philo->data->start_time), philo->index);
	pthread_mutex_lock(philo->right_fork);
	printf("%lld %d has taken a fork\n", elapsed_time(philo->data->start_time), philo->index);
	printf("%lld %d is eating\n", elapsed_time(philo->data->start_time), philo->index);
	usleep(philo->data->time_to_eat / 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	printf("%lld %d is sleeping\n", elapsed_time(philo->data->start_time), philo->index);
	usleep(philo->data->time_to_sleep / 1000);
	printf("%lld %d is thinking\n", elapsed_time(philo->data->start_time), philo->index);
	return (NULL);
}
