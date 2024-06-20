#include <pthread.h>
#include <unistd.h>
#include <iostream>

int resID = 0;
pthread_rwlock_t mRwlock;

void* read_thread(void* params){
    while(true){
        pthread_rwlock_rdlock(&mRwlock);
        std::cout << "Read thread ID: " << pthread_self() << ", resID: " << resID << std::endl;
        sleep(1);
        pthread_rwlock_unlock(&mRwlock);
    }

    return NULL;
}

void* write_thread(void* params){
    while(true){
        pthread_rwlock_wrlock(&mRwlock);
        ++resID;
        std::cout << "Write thread ID: " << pthread_self() << ", resID: " << resID << std::endl;
        pthread_rwlock_unlock(&mRwlock);
        sleep(1);
    }

    return NULL;
}


int main(){
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&mRwlock, &attr);

    pthread_t readThread[5];
    for(int i = 0; i < 5; i++){
        pthread_create(&readThread[i], NULL, read_thread, NULL);
    }

    pthread_t writeThread;
    pthread_create(&writeThread, NULL, write_thread, NULL);
    pthread_join(writeThread, NULL);

    for(int i = 0; i < 5; i++){
        pthread_join(readThread[i], NULL);
    }

    pthread_rwlock_destroy(&mRwlock);

    return 0;
}