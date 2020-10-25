#!/bin/sh
# Popov Yury SKB 172

# 			 Задание:
#
# Написать программу, предоставляющую информацию обо всех активных процессах в системе.
# Передать эту информацию через межпроцессный канал в параллельный процесс и
# вывести в нем идентификаторы всех процессов.
# Предусмотреть возможность неоднократного прерывания от клавиатуры.
# При поступлении четвертого прерывания вывести имена всех задействованных терминалов в системе в настоящее время



# Interruptions
counter=0
 


# SIGINT handler
Handler(){

	# increase interrupt counter
	counter=`expr $counter + 1`
	
	#After fourth time
	test [ $counter -eq 4 ];

		# prints all tty
		ps ax | awk '{print $2}'
		#ps ax
	
}

# rewrite SIGINT handler
trap 'Handler' 2

ps ax | awk '{print $1}'

# cycle for interruptions
while true
do
	echo 'Enter "exit" to stop or Ctrl+C to show names of all currently active terminals in the system '
	read command
	if [ "$command" = "exit" ]; then
		exit 0
	fi
done
