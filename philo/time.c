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
