// Лабораторная работа № 2
//
// Задание. Клиент:
// Записать в РОП, созданную сервером сообщение, содержащее календарь текущего месяца.



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>    // Для shmget()
#include <sys/sem.h>    // Для semget()
#include <string.h>
#include <stdio.h>
#include <unistd.h>   // sleep()


//! Структура sembuf для операций над семафорами
struct sembuf minus  = {0, -2, 0};

//! Объединение для semctl
union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
}arg;


int main(){
        printf("Запускаем клиента. Поехали!!!\n");
	
	//message_t msg1;
        //! Генерируем идентификаторы РОП и семафора
        key_t sem_key, shm_key;

        char *sem_path = ".";
        int id_1 = 'S';
        sem_key = ftok(sem_path, id_1);


        char *shm_path = ".";
        int id_2 = 'K';
        shm_key = ftok(shm_path, id_2);

        printf("Ключ семафора на клиенте: %d\n", sem_key);
        printf("Ключ РОП на клиенте: %d\n", shm_key);
	
	//int semid;
	char *addr;
	
	int semid = -1;

        while(semid == -1){
                semid = semget(sem_key, 1, 0);
        }

	printf("Идентификатор семафоров: %d\n", semid);
	
	

        int  shmid = shmget (shm_key, 1024, 0);
        
	printf("Идентификатор РОП: %d\n", shmid);

	
	//! получение адреса сегмента
	addr = (char *) shmat (shmid, 0, 0);


	char msg[1000] = "cal";
	FILE *f = popen(msg, "r");
	
	char msg2[1000] = "date +%A";
	FILE *f2 = popen(msg2, "r");
	

	char temp1[10];
	fgets(temp1, sizeof(temp1), f2);

	char buffer[1000];
	char temp[1000];
	strncat(buffer, temp1, 10);
	while(fgets(temp, 1000 , f) != NULL){
		strcat(buffer, " \n ");
		strcat(buffer, temp);
		//strcat(buffer, " \n ");
	}
	
	printf("Buffer: %s", buffer);


	//! Ждем пока сервер разблокирует, то есть сможем вычесть 2
	semop(semid, &minus, 1);
	
	//! Записываем в РОП
	strncpy(addr, buffer, 1000);
			
	//! Блокируем, вычитаем еще 2 - делаем значенеи 0
	semop(semid, &minus, 1);		


	shmdt(addr);

	return 0;
	
}
