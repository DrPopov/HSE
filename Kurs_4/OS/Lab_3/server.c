// Лабораторная работа № 3
// Обмен сообщения через гнезда
//
// Попова Юрия СКБ-172
//
// Вариант 11
//
// Сервер. 
// Создать гнездо дейтаграммного типа домена UNIX.
// При поступлении клиентского сообщения определить сколько времени выделенные процессы находились в распоряжении центрального процессора и их приоритет.


#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h> 		// Для структуры sockaddr_un 
#include <unistd.h> 		// Для close()
#include <strings.h>		// Для bzero()

int main(){

	struct sockaddr_un addr, client_addr;
	int sid;	// Пользовательский дескриптор гнезда
	char buff[2048]; // Куда поступает информация от клиента


	// Создаем гнездо
	if( (sid = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1){
		perror("socket error!");
		return -1;
	}

	printf("Польз. дескр. гнезда: %d \n", sid);

	// Очищаем память
	bzero((void *)&addr, sizeof(addr));
	bzero((void *)&client_addr, sizeof(client_addr));

	// Определяем  параметры структуры sockaddr_un
	addr.sun_family  = AF_UNIX;
	strcpy(addr.sun_path,  "./sockname");


	// Присваиваем гнезду имя
	if( bind(sid, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		perror("bind error!");
		return -1;
	};
	
	int len, n;
	

	len = sizeof(client_addr); 

	// Ждем получения сообщения
	n = recvfrom(sid, (char *)buff, 2048, MSG_WAITALL, (struct sockaddr *) &client_addr, &len);
	buff[n] = '\0';

	//char cmd1[124] = "echo";
	//strcat(cmd1, buff);
	//strcat(cmd1, " ");
		
	char cmd[100] = "ps -e -o etimes -o pri";
	FILE *f = popen(cmd, "r");
	char msg[2048];
	fgets(msg, sizeof(msg), f);
	
	printf("Message: %s\n", msg);
	
	// Закрываем соединение между СГ и КГ
	if(shutdown(sid, 2) == -1){
		perror("shutdown error!");
	};
       	
        // Удаляем созданный файл
	remove("./sockname");

	// Закрываем дескрипторы
	close(sid);	
	
	return 0;

}
