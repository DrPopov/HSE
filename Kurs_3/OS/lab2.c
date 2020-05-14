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
#include <stdlib.h>		// для system
int interrupt_counter = 0;	//счетчик прерываний


void interrupt_handler(){
	interrupt_counter++;
	if(interrupt_counter == 4){
		printf("\n");
		
		//if(fork == 0){
			//child process start
			//print all active tty's in system right now
			
		//}else{
			//parent's process
		//	wait();
		//}

	}
}


int main(){
	int s;
	char m;
	int pipe_descriptors[2];	//pipe IN/OUT descriptors
	pipe(pipe_descriptors);		//init pipe
	char  buff[1000];
	
	if(fork == 0){
		//  процесс сын

		close(pipe_descriptors[0]);	//Происходит только запись в канал
		close(1);
		dup2(pipe_descriptors[1], 1);	// Копируем
		//dup(pipe_descriptors[1])
		close(pipe_descriptors[1]);	//Удаляем копию

		printf("\n");
		system("ps ax");
		exit(0);
	}else{
		// процесс отец

		wait(&s);
		close(pipe_descriptors[1]);	//Происходит только чтение из канала
		close(0);
		dup2(pipe_descriptors[0], 0);
		//dup(pipe_descriptors[0])
		close(pipe_descriptors[0]);
		
		//scanf("%s", buff);
		//char buffer[1000];
		//memset(&buffer, 0, 1000);
		m = read(pipe_descriptors[0], buff, 1000);
		printf("\n%s\n", buff);
	}



	printf("Good luck! Have fun! We finished here");
}

