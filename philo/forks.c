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

int	grab_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->state_mutex);
	if (philo->right_fork < philo->left_fork)
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	else
	{
		first = philo->left_fork;
		second = philo->right_fork;	
	}
	pthread_mutex_lock(first);
	//if (philo->state == HUNGRY)
		print_state(philo, "has taken a fork");
	pthread_mutex_lock(second);
	//if (philo->state == HUNGRY)
		print_state(philo, "has taken a fork");
	return (0);
}
/*
int	grab_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	if (philo->state == DEAD)
		return (1);
	pthread_mutex_lock(fork);
	if (philo->state == HUNGRY)
		print_state(philo, "has taken a fork");
	return (0);
}
*/
/*
void	drop_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}
*/
void	drop_forks(t_philosopher *philo)
{
	//drop_fork(philo->right_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_state(philo, "has dropped a fork");
	//drop_fork(philo->left_fork);
	pthread_mutex_unlock(philo->left_fork);
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
