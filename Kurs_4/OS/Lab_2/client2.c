// Лабораторная работа № 2
//
// Задание. Клиент2:
// Записать в РОП, созданную сервером сообщение, хост-имя компьютера



#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>    // Для shmget()
#include <sys/sem.h>    // Для semget()
#include <string.h>
#include <stdio.h>
#include <unistd.h> // sleep()

//! Структура sembuf для операций над семафорами
struct sembuf minus[]  = {0,   -5, 0};

//! Объединение для semctl
union semun{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
}arg;


int main(){

        //! Поехали
        printf("Запускаем клиента 2. Поехали!!!\n");


        //! Генерируем идентификаторы РОП и семафора
        key_t sem_key, shm_key;

        char *sem_path = ".";
        int id_1 = 'S';
        sem_key = ftok(sem_path, id_1);


        char *shm_path = ".";
        int id_2 = 'K';
        shm_key = ftok(shm_path, id_2);

        printf("Ключ семафора на клиенте_2: %d\n", sem_key);
        printf("Ключ РОП на клиенте_2: %d\n", shm_key);

	//int semid;
	char *addr;
	
	
	int semid = -1;
	
	while(semid == -1){
		semid = semget(sem_key, 1, 0);
	}
        
	printf("Идентификатор семафоров: %d\n", semid);

        int shmid = shmget (shm_key, 1024, 0);

        printf("Идентификатор РОП: %d\n", shmid);


        //! получение адреса сегмента
        addr = (char *) shmat (shmid, 0, 0);

	
	char buffer[1000];
        char msg[1000] = "hostname";
        FILE *f = popen(msg, "r");
	fgets(buffer, 1000, f);
	
	printf("Buffer is: %s", buffer);
	
	
	//! Ждем пока значение семафора будет больше или равно 5
        semop(semid, minus, 1);

	// Записываем в РОП
	strncpy(addr, buffer, 1000);

	// Блокируем
	semop(semid, minus, 1);

	
        shmdt(addr);

        return 0;

}
