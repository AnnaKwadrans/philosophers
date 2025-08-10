/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:35:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 20:19:54 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	record_full_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->full_mutex);
	philo->data->full_philos++;
	printf("%d FULL: %d MEALS %d\n", philo->index, philo->data->full_philos, philo->nb_of_meals);
	pthread_mutex_unlock(&philo->data->full_mutex);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	//if (philo->index % 2 == 0)
	//	ft_usleep(philo->time_to_eat / 2);
	if (philo->nb_of_philos == 1)
		return (print_state(philo, "has taken a fork"), NULL);
	while (1)
	{
		if (grab_forks(philo) > 0)
			break ;
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
	if (has_dinner_finished(philo->data))
		return (1);
	print_state(philo, "is eating");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = elapsed_time(philo->start_time);
	pthread_mutex_unlock(&philo->last_meal_mutex);
	philo->nb_of_meals++;
	if (philo->max_meals > 0 && philo->nb_of_meals == philo->max_meals)
		record_full_philo(philo);
	ft_usleep(philo->time_to_eat);
	return (0);
}

int	sleeping(t_philosopher *philo)
{
	if (has_dinner_finished(philo->data))
		return (1);
	print_state(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int	thinking(t_philosopher *philo)
{
	if (has_dinner_finished(philo->data))
		return (1);
	print_state(philo, "is thinking");
	//ft_usleep((philo->time_to_die - philo->time_to_eat
	//		- philo->time_to_sleep) / 2);
	return (0);
}
