/*
Argumentos: 
	number_of_philosophers
	time_to_die
	time_to_eat
	time_to_sleep
	[number_of_times_each_philosopher_must_eat]

Funciones autorizadas:
	memset			pthread_create
	printf			pthread_detach
	malloc			pthread_join
	free			pthread_mutex_init
	write			pthread_mutex_destroy
	usleep			pthread_mutex_lock
	gettimeofday		pthread_mutex_unlock
*/

#include "philo.h"

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int	i = 0;
	
	//printf("value of x in t1: %d\n", x);
	while (i < 1000000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
		i++;
	}
	//usleep(2500000);
	//printf("value of x in t1: %d\n", x);
	return (NULL);
}
/*
void	*routine2()
{
	printf("value of x in t2: %d\n", x);
	usleep(5000000);
	printf("value of x in t2: %d\n", x);
	return (NULL);
}
*/

void	*roll_dice()
{
	int	n;
	int	*res;

	res = (int *)malloc(sizeof(int));
	n = (rand() % 6) + 1;
	*res = n;
	//printf("%d\n", n);
	return ((void *)res);
}

int	main(int argc, char **argv)
{
	pthread_t	*t;
	int		i;
	int		*res;

	srand(time(NULL));
	if (argc != 2 || atoi(&argv[1][0]) == 0)
	{
		printf("no philosophers number\nexit\n");
		return (0);
	}
	t = (pthread_t *)malloc(sizeof(pthread_t) * (atoi(&argv[1][0]) + 1));
	if (!t)
		return (3);
	pthread_mutex_init(&mutex, NULL);
	i = 0;
	while (i < atoi(&argv[1][0]))
	{
		if (pthread_create(t + i, NULL, &roll_dice, NULL) != 0)
			return (1);
		printf("thread %d initiated\n", i);
		i++;
	}
	i = 0;
	while (i < atoi(&argv[1][0]))
	{
		if (pthread_join(t[i], (void **)&res) != 0)
			return (2);
		printf("thread %d finished\n", *res);
		i++;
	}
	free(t);
	t = NULL;
	free(res);
	res = NULL;
	pthread_mutex_destroy(&mutex);
	printf("value of x after threads: %d\n", mails);
	return (0);
}
