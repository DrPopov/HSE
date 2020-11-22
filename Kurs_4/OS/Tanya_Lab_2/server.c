// Татьяная Козликина 
// Студент группы СКБ-172 
// Вариант- 8
//
// Задание: 
// Сервер. Создать разделяемую область памяти (РОП) и набор семафоров(НС). 
// Записать в РОП текущую дату и время,  имена всех пользователей, работающих в настоящее время в системе и  хост-имя компьютера. 
// Сообщения, полученные от клиентов, распечатывать.
//  В конце сеанса удалить РОП и НС.


#include <sys/types.h>	// Для кроссплатформенности
#include <sys/ipc.h>
#include <sys/shm.h>    // Для shmget()
#include <sys/sem.h>    // Для semget()
#include <string.h>
#include <stdio.h>


//! Структура сообщения, помещающемого в РОП
typedef struct{
        int type;
        char text[1024];

} message_t;

//! Структура sembuf для операций над семафорами
//struct sembuf minus[1] = {{0,  -2, 0}};



//! Объединение для semctl
union semun{
        int val;
        struct semid_ds *sbuf;
        ushort *array;
}arg;

int main(){
	//Поехали! 
	printf("Сервер запустился. Начинаем!\n");

	//! Генерируем идентификаторы РОП и семафора
        key_t sem_key, shm_key;

        char *sem_path = "/etc/";
        int sem_id = 'T';
        sem_key = ftok(sem_path, sem_id);


        char *shm_path = "/etc/";
        int shm_id = 'K';
        shm_key = ftok(shm_path, shm_id);

        printf("Ключ семафора на сервере: %d\n", sem_key);
        printf("Ключ РОП на сервере: %d\n", shm_key);


        //! Создаем массив семафор из одного элемента
        int semid;
        if((semid = semget(sem_key, 1, IPC_CREAT | 0644)) < 0)
                perror("Сервер: невозможно создать семафор!");

        printf("Идентификатор семафоров: %d\n", semid);

        //! Создаем сегмент разделяемой памяти
        int shmid;
        if((shmid = shmget(shm_key, 1024, IPC_CREAT | 0644)) < 0)
                perror("Сервер: немозможно осздать разделяемую область памяти!");

        printf("Идентификатор РОП: %d\n", shmid);


        //! Подключение РОП к адресному пр-ву процесса
        message_t *addr;
        addr = (message_t *) shmat(shmid, 0, 0);

	// ---------------------------------------------------
	//message_t *m1, *m2, *m3;	// Адреса сообщений в РОП


	char msg1[1000] = "date";
	char msg2[1000] = "who | awk {'print $1'}";
	char msg3[1000] = "hostname";

	FILE *f1 = popen(msg1, "r");
        FILE *f2 = popen(msg2, "r");
        FILE *f3 = popen(msg3, "r");

	char buffer1[1000], buffer2[1000], buffer3[1000];
	fgets(buffer1, 1000, f1);	
		
	
	// Устанавливаем начальное значение семафора равное 0
	arg.val = 0;
	semctl(semid, 0, SETVAL, arg);

	// Записываем требуемые сообщения в РОП
	strncpy(addr->text, buffer1, 1000);



	
}

