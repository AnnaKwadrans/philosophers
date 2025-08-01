/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:18:29 by akwadran          #+#    #+#             */
/*   Updated: 2025/08/01 16:17:11 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	valid_arguments(int argc, char **argv)
{
	if (!valid_number_of_args(argc) || !are_args_valid_numbers(argv))
		return (0);
	return (1);
}

bool	valid_number_of_args(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("usage:\n./philo number_of_pfilosophers time_to_die time_to_eat");
		printf(" time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	return (1);
}

bool	are_args_valid_numbers(char **argv)
{
	long	num;
	int	i;

	i = 0;
	while (argv[i])
	{
		num = ft_atol();
	}
}
