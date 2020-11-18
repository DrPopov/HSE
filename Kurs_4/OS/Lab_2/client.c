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


/* коды сообщений */

#define MSG_TYPE_EMPTY  0 /* пустое сообщение */
#define MSG_TYPE_STRING 1 /* тип сообщения о том, что
                             передана непустая строка */
#define MSG_TYPE_FINISH 2 /* тип сообщения о том, что
                             пора завершать обмен */
#define MAX_STRING	120



//! Структура сообщения
struct message{
        int type;
        char text[1024];

};

//! Структура sembuf для операций над семафорами
struct sembuf plus[1]  = {{0, 	2, 0}};


//! Объединение для semctl
union semun{
	int val;
	struct semid_ds *sbuf;
	ushort *array;
}arg;


int main(){

	char buffer[1024];
	struct semid_ds buf;
	struct shmid_ds sbuf;
        //! Поехали
        printf("Запускаем клиента. Поехали!!!\n");

	struct message msg1;
	

        //! Генерируем идентификаторы РОП и семафора
        key_t sem_key, shm_key;

        char *sem_path = ".";
        int id_1 = 'S';
        sem_key = ftok(sem_path, id_1);


        char *shm_path = ".";
        int id_2 = 'K';
        shm_key = ftok(shm_path, id_2);

        printf("Semaphore key on client is: %d\n", sem_key);
        printf("Shared memory key on client is: %d\n", shm_key);


	//!Получить доступ к массиву семафоров 
	int semid;
	if ((semid = semget (sem_key, 1, 0)) < 0)
    		perror("Client: can't get semaphore");

 	printf("Идентификатор семафоров: %d\n", semid);	


	//! Получение доступа к сегменту разделяемой памяти
	int shmid;
	if ((shmid = shmget (shm_key, sizeof (msg1.text), 0)) < 0)
    		perror("Client: can't  get shared memory segment");

	printf("Идентификатор РОП: %d\n", shmid);


	//! получение адреса сегмента
	char * addr;
	addr = (char *) shmat (shmid, 0, 0);


	//printf("Адрес РОП: %d\n", &addr);


	char msg[1000] = "cal";
	//char msg[100] = "echo hui";
	FILE *f = popen(msg, "r");
	//fgets(buffer, 1024, f);
	

	//! Устанавливаем начальное значение семафора равное 0
	arg.val = 0;
	semctl(semid, 0, SETVAL, arg);
	
	//! Записываем в РОП
	memcpy(addr, str(&f), 100);
	printf("BUff %s \n", addr);
			
	//! Отменяем блокировку - делаем значенеи 2
	semop(semid, plus, 1);
		

	return 0;
	
}
