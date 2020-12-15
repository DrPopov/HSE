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
	n = recvfrom(sid, (char *)buff, 2048, 0, (struct sockaddr *) &client_addr, &len);
	buff[n] = '\0';

	
	printf("Buff: %s", buff);
	
	char sep[10] = " ";
       	char *istr;	
	istr = strtok(buff, sep);
	
	char cmd0[1024] = " -o etimes -o pri | sed '1d'";
	while(istr != NULL){
		char cmd[1024] = "ps -p ";
		strcat(cmd, istr);
		strcat(cmd, cmd0);
		
		FILE *f = popen(cmd, "r");
	        char msg[2048];
        	fgets(msg, sizeof(msg), f);
		printf("%s\n", msg);

		istr = strtok(NULL, sep);
	}
	remove("./sockname");

	// Закрываем дескрипторы
	close(sid);	
	
	return 0;

}
