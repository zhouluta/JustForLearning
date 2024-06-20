#include <stdio.h>
#include <thread>
#include <unistd.h>

void threadproc1(){
	while(1){
		printf("I am thread 1: %u!\n", std::this_thread::get_id());
		sleep(1);
	}
}

void threadproc2(){
	while(1){
		printf("I am thread 2: %u!\n", std::this_thread::get_id());
		sleep(1);
	}
}

int main(){
	std::thread t1(threadproc1);
	std::thread t2(threadproc2);
	
	while(1){
		
	}
	return 0;
}
