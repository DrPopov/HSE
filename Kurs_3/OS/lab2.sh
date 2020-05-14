# Popov Yury SKB 172

#  Задание:
# Написать программу, предоставляющую информацию обо всех актив-ных процессах в системе.
# Передать эту информацию через межпро-цессный канал в параллельный процесс и
# вывести в нем идентифика-торы всех процессов.
# Предусмотреть возможность неоднократного прерывания от клавиатуры.
# При поступлении четвертого прерывания вывести имена всех задействованных терминалов в системе в настоящее время


#ps ax | awk '{print $1 " " $4}'

# Interruptions
counter=0
 


# SIGINT handler
Handler(){
	# just for beauty
	echo ''

	# increase interrupt counter
	counter=`expr $counter + 1`
	
	# every odd interruption
	if [ $counter -eq 4 ]; then

		# prints all tty
		# ps | cut -c 7-14
		ps ax | awk '{print $2}'
	fi
}

# rewrite SIGINT handler
trap 'Handler' 2

#ps | cut -c -6
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
