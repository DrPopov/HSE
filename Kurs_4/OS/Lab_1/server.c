/**
 * Сервер.
 * Выбрать из очереди 1-ое сообщение.
 * Определить все файлы из сообщения, в которых используется фильтр «awk»,
 * подсчитать их количество и определить максимальное число байтов всех сообщений очереди.
 *
 */
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>

#define MSGMAX 1024

struct msgbuf{
    long mtype;
    char text[1024];
}msg1, msg2, msg3;

int main(){

	struct msqid_ds ds;

	printf("\nСервер зпустился!\n");
	
	//! Генерируем точно такой же индефикатор 
	key_t key;
	char *path = ".";
	int id = 'S';
	key = ftok(path, id);
	printf("Key on server is %d\n", key);

	// Открываем очередь
	int msqid = msgget(key, 0);

	if(msqid == -1)
		perror("Ошибка msget");


	// Получаем сообщения
	if(msgrcv(msqid, &msg1, sizeof(msg1.text), 1, 0) < 0 ){
		perror("Problems with msgrcv");
	}

	printf("Первое полученное сообщение: %s", msg1.text);

	// Получаем сообщения
        if(msgrcv(msqid, &msg2, sizeof(msg2.text), 2, 0) < 0 ){
                perror("Problems with msgrcv");
        }

        printf("\nВторое полученное сообщение: %s", msg2.text);

	// Получаем сообщения
        if(msgrcv(msqid, &msg3, sizeof(msg3.text), 3, 0) < 0 ){
                perror("Problems with msgrcv");
        }

        printf("\nТретье полученное сообщение: %s", msg3.text);



	// 1.Определить все файлы из сообщения, в которых используется фильтр «awk»
	char awk_files[1024];
	char cmd1[] = "grep -l awk  ";
	strcat(cmd1, msg1.text);
	strcat(cmd1, " | tr '\n' ' '");	

	FILE *f1 = popen(cmd1, "r");
	fgets(awk_files, MSGMAX, f1);
	printf("\nФайлы из сообщения, в которых используется фильтр «awk: %s", awk_files);
	
	char tmp[1024];
	strncpy(tmp, awk_files, sizeof(awk_files));

	// 2. Их количество:
	char amount[1024];
	char cmd2[] = "grep -l awk ";
	strcat(cmd2, awk_files);
	strcat(cmd2, " |  wc -l");

	FILE *f2 = popen(cmd2, "r");
	fgets(amount, MSGMAX, f2);
	printf("\nКоличество файлов: %s", amount);


	// 3. Максимальное число байтов всех сообщений
	char max_size[1024];
	char cmd3[] = "ls -Sl ";
	strcat(cmd3, tmp);
	strcat(cmd3, " | awk '{print $5}' | head -n 1");
	
	FILE *f3 = popen(cmd3, "r");
	fgets(max_size, MSGMAX, f3);
	printf("Максимальное число байтов всех сообщений: %s\n", max_size);	

}
