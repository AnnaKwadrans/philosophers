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
		mails++;
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
int	main(int argc, char **argv)
{
	pthread_t	t1;
	pthread_t	t2;
	int		pid;

	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0)
		return (4);
	/*
	pid = fork();
	if (pid == -1)
		return (5);
	printf("value of x in p: %d\n", x);
	if (pid == 0)
		x++;
	usleep(5000000);
	*/
	pthread_mutex_destroy(&mutex);
	printf("value of x after threads: %d\n", mails);
	return (0);
}
