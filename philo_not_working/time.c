/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:44:37 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/03 17:45:21 by akwadran         ###   ########.fr       */
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
	printf("%lld %d %s\n", elapsed_time(philo->data->start_time), philo->index, msg);
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
		//printf("ELAPSED %lld\n", elapsed);
		rem = time - elapsed;
		//printf("REMAINING %lld\n", rem);
		if (rem > 1000)
			usleep(rem / 2);
	}
}
/*
int	main(void)
{
	long long	ts;
	int			i;
	long long	start;

	i = 200;
	start = get_timestamp();
	while (i < 1000)
	{
		ts = get_timestamp() - start; 
		printf("start %lld | i = %d\n", ts, i);
		ft_usleep(i);
		ts = get_timestamp() - start;
		printf("end %lld\n", ts);
		i += 300;
	}
}*/