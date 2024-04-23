#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_KEY 1234

struct my_msgbuf {
	long mtype;
	char mtext[100];
};

int main() {
	key_t key = ftok("progfile", MSG_KEY);
	int msgid = msgget(key, 0666 | IPC_CREAT);

	struct my_msgbuf msg;
	msg.mtype = 1;
	strcpy(msg.mtext, "Shutting down the system now...");

	msgsnd(msgid, &msg, sizeof(msg.mtext), 0);

	system("sudo shutdown -h now");

	return 0;
}