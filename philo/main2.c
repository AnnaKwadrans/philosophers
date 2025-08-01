#include "philo.h"

int	primes[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };
pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	int	*num;
	int	*sum;
	int	i;

	num = (int *)arg;
	sum = (int *)malloc(sizeof(int));
	*sum = 0;
	i = 0;
	while (i < 5)
	{
		*sum += num[i];
		i++;
	}
	//printf("index: %d, prime number: %d\n", index, primes[index]);
	free(arg);
	//printf("%d\n", index);
	return ((void *)sum);
}

int	main(void)
{
	pthread_t	th[10];
	int	i;
	int	*aux;
	int	*ret;

	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < 2)
	{
		aux = (int *)malloc(sizeof(int));
		*aux = i * 5;
		//printf("i: %d\n", i);
		if (pthread_create(&th[i], NULL, &routine, primes + i) > 0)
			return (perror("failed to create thread"), 1);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) > 0)
			return (perror("failed to join thread"), 1);
		i++;
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}