// Лабораторная работа № 2
// Попова Юрия СКБ-172
// Вараинт - 11
//
// Задание. Сервер:
// Создать разделяемую область памяти (РОП) и набор семафоров (НС).
// При поступлении клиентского сообщения о календаре текущего месяца, определить текущий день недели по текущей дате
//
//
// Удалить РОП и НС.
//


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>	// Для shmget()
#include <sys/sem.h>	// Для semget()
#include <string.h>
#include <stdio.h>
#include <unistd.h>

//! Структура sembuf для операций над семафорами
struct sembuf equal = {0, 0, 0};

//! Объединение для semctl
union semun{
        int val;
        struct semid_ds *sbuf;
        ushort *array;
}arg;


int main(){
	//! Поехали
	printf("Запускаем сервак. Поехали!!!\n");



	//! Генерируем идентификаторы РОП и семафора
        key_t sem_key, shm_key;

        char *sem_path = ".";
	int sem_id = 'S';
	sem_key = ftok(sem_path, sem_id);


	char *shm_path = ".";
	int shm_id = 'K';
	shm_key = ftok(shm_path, shm_id);
        
	printf("Ключ семафора на сервере: %d\n", sem_key);
	printf("Ключ РОП на сервере: %d\n", shm_key);


	//! Создаем массив семафор из одного элемента
	int semid;
	if((semid = semget(sem_key, 1, IPC_CREAT | 0644)) < 0)
		perror("Server: can't create semaphore");

	printf("Идентификатор семафоров: %d\n", semid);

	//! Создаем сегмент разделяемой памяти
	int shmid;
	if((shmid = shmget(shm_key, 1024, IPC_CREAT | 0644)) < 0)
		perror("Server: can't create shared memory segment");
	
	printf("Идентификатор РОП: %d\n", shmid);
	

	//! Подключение РОП к адресному пр-ву процесса
	char *addr;
	addr = (char *) shmat(shmid, 0, 0);
	

	//! Устанавливаем начальное значение семафора равное 4
        arg.val = 4;
        semctl(semid, 0, SETVAL, arg);
	printf("Arg is 4!\n");
	semop(semid, &equal, 1);

	printf("Today is: %s\n", addr);
	
	arg.val = 10;
	semctl(semid, 0, SETVAL, arg);
	printf("Arg is 10!\n");
	semop(semid, &equal, 1);

	printf("Hostname: %s\n", addr);

	//! Отсоединяем РОП
	if(shmdt(addr) == -1) perror("Server: error with shmdt");
	
	//! Удаляем РОП
	if(semctl(semid, 0, IPC_RMID, 0) == -1) perror("Server: erorr with semctl");
	if(shmctl(shmid, IPC_RMID, 0) == -1) perror("Server: error with shmctl");

	return 0;
}
