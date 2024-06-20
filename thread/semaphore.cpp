#include <list>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

class Task{
    public:
        Task(int TaskID){
            this->taskID = TaskID;
        }

        void doTask(){
            std::cout << "Handle a task, taskID: " << this->taskID << " threadID: " << pthread_self() << std::endl;
        }

    private:
        int taskID;
};

pthread_mutex_t mMutex;
std::list<Task*> tasks;
sem_t mSemaphore;

void* consumerThread(void* param){
    Task* pTask = NULL;
    while(true){
        if(sem_wait(&mSemaphore) != 0){
            continue;
        }

        if(tasks.empty()){
            continue;
        }

        pthread_mutex_lock(&mMutex);
        pTask = tasks.front();
        tasks.pop_front();
        pthread_mutex_unlock(&mMutex);
        pTask->doTask();
        delete pTask;
    }

    return NULL;
}

void* producerThread(void* param){
    int taskID = 0;
    Task* pTask = NULL;

    while(true){
        pTask = new Task(++taskID);
        pthread_mutex_lock(&mMutex);
        tasks.push_back(pTask);
        std::cout << "Produced Task: " << taskID << ", thread ID: " << pthread_self() << std::endl;
        pthread_mutex_unlock(&mMutex);

        sem_post(&mSemaphore);
        sleep(1);
    }

    return NULL;
}

int main(){
    pthread_mutex_init(&mMutex, NULL);
    sem_init(&mSemaphore, 0, 0);

    pthread_t consumerThreadID[5];
    for(int i = 0; i < 5; ++i){
        pthread_create(&consumerThreadID[i], NULL, consumerThread, NULL);
    }

    pthread_t producerThreadID;
    pthread_create(&producerThreadID, NULL, producerThread, NULL);

    pthread_join(producerThreadID, NULL);

    for(int i = 0; i < 5; ++i){
        pthread_join(consumerThreadID[i], NULL);
    }

    pthread_mutex_destroy(&mMutex);
    sem_destroy(&mSemaphore);

    return 0;

}
