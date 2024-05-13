#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

pthread_mutex_t mutex;
int counter = 0;

void* thread_woker(void* param){
    pthread_t threadID = pthread_self();
    for(int i = 0; i < 5; ++i){
        pthread_mutex_lock(&mutex);
        printf("Thread %d start: lock mutex.\n", threadID);
        ++counter;
        printf("Counter: %d.\n", counter);
        pthread_mutex_unlock(&mutex);
        printf("Thread %d end: unlock mutex.\n", threadID);
    }

    return NULL;
}

int main(){
    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
    pthread_mutex_init(&mutex, &mutex_attr);

    pthread_t threads[3];
    for(int i = 0; i < 3; ++i){
        pthread_create(&threads[i], NULL, thread_woker, NULL);
    }

    for(int i = 0; i < 3; ++i){
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_mutexattr_destroy(&mutex_attr);

    return 0;
}