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

bool	has_dinner_finished(t_data *data)
{
	bool	finish;

	pthread_mutex_lock(&data->finish_mutex);
	finish = data->finish;
	pthread_mutex_unlock(&data->finish_mutex);
	return (finish);
}

void	record_full_philo(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->full_mutex);
	philo->data->full_philos++;
	pthread_mutex_unlock(&philo->data->full_mutex);
	change_state(philo, FULL);
}
/*
void	*routine(void *arg)
{
	t_philosopher	*philo;
	t_data			*data;

	philo = (t_philosopher *)arg;
	data = philo->data;
*/
	//all_ths_created(data);
	//if (philo->index % 2 == 0)
	//	ft_usleep(philo->data->time_to_eat / 2);
	//pthread_mutex_lock(&data->finish_mutex);
	//if (data->finish)
	//{
	//	pthread_mutex_unlock(&data->finish_mutex);
	//	return (NULL);
	//}
/*
	while (!has_dinner_finished(data))
	{
		//pthread_mutex_unlock(&data->finish_mutex);
		if (philo->index % 2 == 0)
			ft_usleep(philo->data->time_to_eat / 2);
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
*/

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;

	all_ths_created(philo->data);
	//if (philo->index % 2 == 0)
	//	ft_usleep(philo->data->time_to_eat / 2);
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
	printf("ROUTINE %d ENDED\n", philo->index);
	return (NULL);
}

int	eating(t_philosopher *philo)
{
	if (!check_state(philo, HUNGRY) || has_dinner_finished(philo->data))
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
	if (!check_state(philo, HUNGRY) || has_dinner_finished(philo->data))
		return (1);
	print_state(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int	thinking(t_philosopher *philo)
{
	if (!check_state(philo, HUNGRY) || has_dinner_finished(philo->data))
		return (1);
	print_state(philo, "is thinking");
	if (philo->index % 2 == 0)
		ft_usleep(philo->time_to_eat / 2);
	return (0);
}

void	all_ths_created(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->start_mutex);
		if (data->start)
		{
			pthread_mutex_unlock(&data->start_mutex);
			printf("ALL THS CREATED\n");
			return ;
		}
		pthread_mutex_unlock(&data->start_mutex);
		//usleep(2);
	}
}
