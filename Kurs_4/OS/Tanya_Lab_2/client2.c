// Татьяная Козликина 
// Студент группы СКБ-172 
// Вариант- 8
//
// Задание: 
// Клиент 2. Выбрать из РОП текущую дату и время и определить по ним день недели, а также количество семафоров в наборе.
//


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>    // Для shmget()
#include <sys/sem.h>    // Для semget()
#include <string.h>
#include <stdio.h>


struct message{
        int type;
        char text[1024];

};

//! Структура sembuf для операций над семафорами
struct sembuf plus[1]  = {{0,   2, 0}};


//! Объединение для semctl
union semun{
        int val;
        struct semid_ds *buf;
        unsigned short *array;
}arg;


int main(){

        //char buffer[1024];
        //struct semid_ds buffer;
        //struct shmid_ds sbuf;
        //! Поехали
        printf("Запускаем клиента. Поехали!!!\n");

        struct message msg1;


        //! Генерируем идентификаторы РОП и семафора
        key_t sem_key, shm_key;

        char *sem_path = "/etc/";
        int sem_id = 'T';
        sem_key = ftok(sem_path, sem_id);


        char *shm_path = "/etc/";
        int shm_id = 'K';
	shm_key = ftok(shm_path, shm_id);


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

}
