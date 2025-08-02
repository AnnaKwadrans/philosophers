/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:35:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/02 14:37:21 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->state == DEAD)
		return (NULL);
	while (philo->state == ALIVE)
	{
		if (grab_fork(philo, philo->right_fork) > 0)
			break ;
		if (grab_fork(philo, philo->left_fork) > 0)
		{
			drop_fork(philo->left_fork);
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
	return (NULL);
}

int	grab_fork(t_philosopher *philo, pthread_mutex_t *fork)
{
	if (philo->state == DEAD)
		return (1);
	pthread_mutex_lock(fork);
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
	drop_fork(philo->left_fork);
}

int	eating(t_philosopher *philo)
{
	if (philo->state == DEAD)
		return (1);
	print_state(philo, "is eating");
	philo->last_meal = elapsed_time(philo->data->start_time);
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

void	print_state(t_philosopher *philo, char *msg)
{
	printf("%lld %d %s\n", elapsed_time(philo->data->start_time), philo->index, msg);
}

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
			if (philo[i].state == ALIVE && has_died(&philo[i], data->time_to_die))
			{
				philo[i].state = DEAD;
				data->count++;
				print_state(&philo[i], "died");
				pthread_join(philo[i].th, NULL);
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
