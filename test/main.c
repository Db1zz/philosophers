#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

void	*thread_routine(void *aboba)
{
	while (true)
		printf("Hello from child thread\n");
	return (NULL);
}

int main(void)
{
	pid_t	pid;
	pid = fork();
	if (pid == 0)
	{
		sem_t *sem = sem_open("Hallo", O_CREAT, 0644, 0);
		pthread_t	thread;
		pthread_create(&thread, NULL, thread_routine, NULL);
		sem_wait(sem);
		while(true) {
			printf("Hallo from child\n");
		}
	}
	else
	{
		waitpid(-1, NULL, 0);
	}
	return (0);
}