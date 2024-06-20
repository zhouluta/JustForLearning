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
pthread_cond_t mCond;

void* consumerThread(void* param){
    Task* pTask = NULL;
    while(true){
        pthread_mutex_lock(&mMutex);
        while(tasks.empty()){
            pthread_cond_wait(&mCond, &mMutex);
        }
        pTask = tasks.front();
        tasks.pop_front();
        pthread_mutex_unlock(&mMutex);
        if(pTask == NULL){
            continue;
        }
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

        pthread_cond_signal(&mCond);
        sleep(1);
    }

    return NULL;
}

int main(){
    pthread_mutex_init(&mMutex, NULL);
    pthread_cond_init(&mCond, NULL);

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
    pthread_cond_destroy(&mCond);

    return 0;

}
