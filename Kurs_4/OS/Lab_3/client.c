// Лабораторная работа № 3
// Обмен сообщения через гнезда
//
// Попова Юрия СКБ-172
//
// Вариант 11
//Клиент. 
//Создать гнездо дейтаграммного типа домена UNIX.
//Выявить среди активных процессов, управляемых терминалами, процессы находящиеся в состоянии «S» и переслать эту информацию в серверное гнездо.


#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>             // Для структуры sockaddr_un
#include <unistd.h>             // Для close()
#include <strings.h>            // Для bzero()



int main(){

        struct sockaddr_un addr;
        int sid;        // Пользовательский дескриптор гнезда
        char buffr[2048]; // Куда поступает информация от клиента


        // Получаем дескриптор  гнезда
        if(( sid = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1){
                perror("socket error!");
                return -1;
        }

        printf("Польз. дескр. гнезда: %d\n", sid);

        // Очищаем память
        bzero((void *)&addr, sizeof(addr));

        // Определяем  параметры структуры sockaddr_un
        addr.sun_family  = AF_UNIX;
        strcpy(addr.sun_path,  "./sockname");

	char cmd[100] = "ps a -e | awk '{print $1 \"\\t\" $3}'  | grep 'S$' |  awk '{print $1}'";
        FILE *f = popen(cmd, "r");
	char  temp[2048];
	fgets(temp, sizeof(temp), f);

	
	printf("Msg: %s\n", temp);
        char *hello = "Hello from Hell! Hah";


	// Отправляем сообщение
	sendto(sid, (char *) temp, strlen(temp), MSG_CONFIRM, (struct sockaddr *)&addr, sizeof(addr));
       // sendto(sid, (char *) hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *)&addr, sizeof(addr));
	
	printf("Message to server sent!\n");

        return 0;

}

