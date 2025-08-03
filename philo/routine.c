/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:35:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 18:14:19 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->state == DEAD)
		return (NULL);
	while (philo->state == ALIVE && philo->nb_of_meals
		< philo->data->number_of_times_each_philosopher_must_eat)
	{
		if (grab_fork(philo, philo->right_fork) > 0)
			break ;
		if (grab_fork(philo, philo->left_fork) > 0)
		{
			drop_fork(philo->left_fork);
			print_state(philo, "has dropped a fork");
			break ;
		}
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
	if (philo->nb_of_meals == philo->data->number_of_times_each_philosopher_must_eat)
		philo->state = FULL;
	pthread_join(philo->th, NULL);
	print_state(philo, "thread joined");
	return (NULL);
}

int	eating(t_philosopher *philo)
{
	if (philo->state == DEAD)
		return (1);
	print_state(philo, "is eating");
	philo->last_meal = elapsed_time(philo->data->start_time);
	philo->nb_of_meals++;
	usleep(philo->data->time_to_eat * 1000);
	return (0);
}

int	sleeping(t_philosopher *philo)
{
	if (philo->state == DEAD)
		return (1);
	print_state(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
	return (0);
}

int	thinking(t_philosopher *philo)
{
	if (philo->state == DEAD)
		return (1);
	print_state(philo, "is thinking");
	return (0);
}
