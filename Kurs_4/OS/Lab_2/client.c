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


//! Структура сообщения
struct message{
        int type;
        char text[1024];

};



int main(){
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


	/* получение адреса сегмента */
	char * addr;
	if ((addr = (char *) shmat (shmid, 0, 0)) == NULL)
		perror("Client: shared memory attach error");


	printf("Адрес РОП: %d\n", &addr);

}
