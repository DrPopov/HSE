/**
* Клиент.
* Создать очередь сообщений. Записать
* в качестве 1-ого сообщения имена всех командных файлов текущего каталога,
* в качестве 2-го сообщения – общее количество строк этих файлов,
* в качестве 3-его сообщения – суммарный размер этих файлов в байтах.
*/

#include <stdio.h>      // Стандартный ввод / вывод
#include <sys/types.h>  // Для кросс-платформености
#include <sys/ipc.h>    // Для макросов и для ipc_perm
#include <sys/msg.h>    //
#include <string.h>     // Для strlen

#define MSGMAX 1024;

struct msgbuf{
    long mtype; // Тип сообщения
    char text[1024]; // Содержание сообщения
} msg1, msg2, msg3;

int main(){

	//! Генерация индефикатора очереди сообщений
	key_t key;
 	char *path = ".";
	int id = 'S';
     	key = ftok(path, id);
     	printf("Key = %d\n", key);

     	//! Создание очереди.
     	int msqid = msgget(key, IPC_CREAT | 0644);
     	printf("MSQID = %d\n", msqid);


     	//! Первое сообщение - имена всех командных файлов текущего каталога
    	char cmd1[] = "file * | grep shell | awk '{print $1}' | sed 's/.$//' | tr '\n' ' '";
	//char cmd1[] = "file * | grep shell | awk '{print $1}'";
     	FILE *f1 = popen(cmd1, "r");
	
     	msg1.mtype = 1;
	
	//(msg1.text, f1);

     	fgets(msg1.text, sizeof(msg1.text), f1);
     	printf("First massage: %s\n", msg1.text);
     	pclose(f1);
    	//! Отправляем первое сообщение
    	if( msqid == -1 || msgsnd(msqid, &msg1,  strlen(msg1.text),  IPC_NOWAIT)){
	    	perror("Message 1 error!");
    	};


	//! Второе сообщение - общее количество строк этих файлов
        //char cmd2[] = "file * | grep shell | wc -l | tr '\n' ' '";
        char cmd2[] = "file * | grep shell | wc -l";
	FILE *f2 = popen(cmd2, "r");

        msg2.mtype = 2;

	fgets(msg2.text, sizeof(msg2.text), f2);
	printf("Second message: %s", msg2.text);
	pclose(f2);
       //! Отправляем второе сообщение
	if( msqid == -1 || msgsnd(msqid, &msg2,  strlen(msg2.text),  IPC_NOWAIT)){
       		perror("Message 2 error!");
       	};


       	//! Третье сообщение - суммарный размер этих файлов в байтах
       	//char cmd3[] = "file * | grep shell | wc -c | tr '\n' ' '";
	char cmd3[] = "file * | grep shell | wc -c ";

	FILE *f3 = popen(cmd3, "r");
	msg3.mtype = 3;
       	
	fgets(msg3.text, sizeof(msg3.text), f3);
	printf("Third message: %s", msg3.text);
	pclose(f3);
	//! Отправляем третье сообщение
       	if( msqid == -1 || msgsnd(msqid, &msg3,  strlen(msg3.text), IPC_NOWAIT)){
	       perror("Message 3 error!");
	};

	return 0;

}
