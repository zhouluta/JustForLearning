#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/syscall.h>

void* threadfunc(void* args){
	printf("NEW Thread ID: %d.\n", syscall(SYS_gettid));
	return NULL;
}

int main(){
	pthread_t threadid;
	pthread_create(&threadid, NULL, threadfunc, NULL);
	
	printf("NEW Thread ID: %u.\n", threadid);
	printf("Main Thread ID: %u, %d.\n", (pthread_self()), syscall(SYS_gettid));
	sleep(1);
	return 0;
}
