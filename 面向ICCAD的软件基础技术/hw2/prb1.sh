#!/usr/bin/env sh

# ----------------------------------------------------------------
# Author: Zewen-Ye
# Institution: College of Information Science and Electrical Engineering, ZheJiang University
# Usage:
# ./prb1.sh
# ----------------------------------------------------------------


echo "    The option are as follows."
echo "---------------------------------------------------------------------"
echo "    1. List all files in current directory and sub-directories in long format\n    2. List all hidden files in current directory and sub-directories in long format\n    3. Read in a name, report whether it is a file, a user, a device, a command, or nobody\n    4. For a file found early in 1, show it in hexadecimal format if you have executable permission\n    5. Display all processes running on this computer whose ancestor is a process of specified PID\n    6. Let '/usr/bin/ftp' automatically download "demo_inout.c" from our course ftp site\n    q. Quit"
echo "---------------------------------------------------------------------"

while true
do
	echo "    Enter '1' - '6' or 'q'"
	read option
	if [ "$option" = "1" ]
	then 
		ls -alR

	elif [ "$option" = "2" ]
	then
		ls -l .??*

	elif [ "$option" = "3" ]
	then
		echo "input a name!"
		read name
		a3=`cat /etc/passwd |cut -d ':' -f 1 | grep $name`;
		if [ -f $name ];  
		then  
			echo 'it is a file '; 
		elif [ -d $name ];
		then 
			echo 'it is a directory '; 
		elif [ "$a3" != " " ]
			then 
				echo 'it is a user name.'
		else
			echo 'nothing'
		fi;

	elif [ "$option" = "4" ]
	then
		for i in `ls -aR`
		do 
			if [ -x $i ]
			then
				echo "$i"
				hexdump -C $i
			fi
		done

	elif [ "$option" = "5" ]
	then
		echo "Enter the PID that you want to search"
		read PID
		ps -ef |grep $PID

	elif [ "$option" = "6" ]
	then	
		echo "downloading file demo_inout.c\n------------------------------------"
ftp -n<<!
open 10.212.43.214
user anonymous 0
binary
prompt
get Course/ICCAD/demo/demo_inout.c demo_inout.c
close
bye
!

	elif [ "$option" = "q" ]
	then
		echo "ok, will exit"
		exit

	else
		echo "invalid input, try again!"	
	fi;

done