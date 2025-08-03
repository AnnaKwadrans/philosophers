/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:35:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 19:41:51 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == DEAD || philo->state == FULL)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		return (NULL);
	}
	while (philo->state == HUNGRY)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		if (grab_forks(philo) > 0)
			break ;
		/*
		if (grab_fork(philo, philo->right_fork) > 0)
			break ;
		if (grab_fork(philo, philo->left_fork) > 0)
		{
			drop_fork(philo->left_fork);
			print_state(philo, "has dropped a fork");
			break ;
		}
		*/
		if (eating(philo) > 0)
		{
			drop_forks(philo);
			break ;
		}
		drop_forks(philo);
		if (sleeping(philo) > 0)
			break ;
		if (thinking(philo) > 0)
			break ;
	}
	return (NULL);
}

int	eating(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->state_mutex);
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = elapsed_time(philo->data->start_time);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	philo->nb_of_meals++;
	if (philo->nb_of_meals == philo->data->number_of_times_each_philosopher_must_eat)
	{
		pthread_mutex_lock(&philo->state_mutex);
		philo->state = FULL;
		pthread_mutex_unlock(&philo->state_mutex);
	}
	usleep(philo->data->time_to_eat * 1000);
	return (0);
}

int	sleeping(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->state_mutex);
	print_state(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->state_mutex);
	if (philo->state == DEAD)
	{
		pthread_mutex_unlock(&philo->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->state_mutex);
	print_state(philo, "is thinking");
	return (0);
}
