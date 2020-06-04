/*
				Popov Yury SKB - 172

 					Задание:

 Написать программу, предоставляющую информацию обо всех актив-ных процессах в системе.

 Передать эту информацию через межпро-цессный канал в параллельный процесс и
 вывести в нем идентифика-торы всех процессов.

 Предусмотреть возможность неоднократного прерывания от клавиатуры.

 При поступлении четвертого прерывания вывести имена всех задействованных терминалов в системе в настоя-щее время.
*/

#include <stdio.h>
#include <unistd.h>		//для  fork
#include <sys/types.h>		//для  wait
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>		//for system
#include <string.h>

int interrupt_counter = 0;	//счетчик прерываний

void interrupt_handler(){
	interrupt_counter++;
	int p;
	if(interrupt_counter == 4){
		//print names of all  active tty's in system 
		write(1, "Fourth itterupt!\n\n", 18);
		
		execl("/bin/ps", "ps", "-A", "-o", "tty=", NULL);
	}
}


int main(){

	//Rewrite the KeyboardInterrupt signal handler
	struct sigaction keyboard_interrupt;
	keyboard_interrupt.sa_handler = interrupt_handler;  // Make our function the handler of KeyboardInterrupt handler
	sigemptyset(&keyboard_interrupt.sa_mask);
        keyboard_interrupt.sa_flags = 0;
	sigaction(SIGINT, &keyboard_interrupt, 0);	

	int s;
	int fd[2];		// Дкскрипторы межпроцессного канала
	pipe(fd);		// Создание межпроцессного канала
	char  buff[80];
	

	if(fork() == 0){ // Распараллеливание процесса
		// Процесс-потомок
		write(1, "Hi, I'm son!\n", 13);
		close(fd[0]);	// Закрытие межпроцессного канала на чтение	
		close(1);	// Закрытие стандартного вывода
		dup2(fd[1], 1);	// Дублирование дескриптора межпроцессного канала на стандартный вывод 
		close(fd[1]);	//Удаляем копию
		system("ps ax"); // Вывод всех активных процессов в системе в межпроцессный канал
		//close(fd[0]);
		exit(0);
		//execl("/bin/ps","ps", "ax", NULL);

	}else{
		// Процесс родитель
		wait(&s);	// Ожидание окончания процесса-потома
		write(1, "Hi, i'm parent!\n", 16);

		//sigsetjmp (obl,1);
		close(fd[1]);	// Закрытие межпроцессного канала на запись
		close(0);	// Закрытие стандартного ввода
		dup2(fd[0], 0);	// Дублирование дескриптора межпроцессного канала на стандартный ввод
		close(fd[0]);	// Удаляем копию
		
		
		//system("awk '{print $1}'");
		execl("/bin/awk", "awk", "'{print $1}'", NULL);
		close(fd[0]);
			
	}

	
	write(1, "\n\nFinish fork!\n\n",16 );
	
	while(getchar() != 'q'){
	}


	printf("Good luck! Have fun! We finished here!!!");
	return 0;
}

