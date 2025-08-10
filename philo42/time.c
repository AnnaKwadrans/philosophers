/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:44:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/10 18:22:36 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp(void)
{
	struct timeval	ts;

	if (gettimeofday(&ts, NULL) < 0)
	{
		printf("error retrieving timestamp\n");
		return (-1);
	}
	return ((ts.tv_sec * 1000) + (ts.tv_usec / 1000));
}

long long	elapsed_time(long long start_time)
{
	return (get_timestamp() - start_time);
}

void	print_state(t_philosopher *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->stdout_mutex);
	printf("%lld %d %s\n", elapsed_time(philo->start_time), philo->index, msg);
	pthread_mutex_unlock(&philo->data->stdout_mutex);
}

void	ft_usleep(long long time)
{
	long long	rem;
	long long	elapsed;
	long long	start;

	elapsed = 0;
	rem = 0;
	start = get_timestamp();
	while (elapsed < time)
	{
		elapsed = get_timestamp() - start;
		rem = time - elapsed;
		if (rem > 10)
			usleep(rem * 1000 / 2);
	}
}
