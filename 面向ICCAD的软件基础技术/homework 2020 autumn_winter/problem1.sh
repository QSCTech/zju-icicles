#! /bin/bash
echo " author : Lin Juyi , college of ISEE, ZHEJIANG UNIVERSITY 1263810658@qq.com"
echo " latest update time : 2020/ 11/14 "
echo " created time : 2020/11/14  for ICCAD class, homework 4_4_3, problem 1  "
echo "---------------------------------------------------------------------"
echo "    The option are as follows."
echo "---------------------------------------------------------------------"
echo "
1. List all (including hidden) files in /usr and its sub-directories in long format
2. List only hidden files in /usr and its sub-directories in long format
3. Input a name, report whether it is a file, a user, a device, a command, or nobody
4. Input a file name, if the file is "un-writeable", try to change it to "writeable" and report whether succeed
5. Read in a file name, show it in hexadecimal format if you have executable permission
6. Let '/usr/bin/ftp' automatically download "1KB.zip" from ftp://speedtest.tele2.net
7. *Display the process running on this computer who is the deepest-low in ‘pstree’
q. Quit "
echo "---------------------------------------------------------------------"


while true
do
	echo "                 Enter '1' - '7' or 'q'"
	read option
	if [ "$option" = "1" ]
	then 
		cd /usr
		ls -al 
		echo “successful operate option 1”
	elif [ "$option" = "2" ]
	then
		cd /usr
		ls -ld .??*
		echo “successful operate option 2”
	elif [ "$option" = "3" ]
	then
	   	echo "input a name!"
		read name
		echo 'the name you input is that: ';
		echo $name ;
		if [ -f "$name" ]
		then
			echo 'it is a file ';
		elif [ -d "$name"  ]
		then
			echo 'it is a directory ';
		elif [  -b ${name} -o -c ${name}   ]
		then
			# -c for char device  -b for block device
			echo 'it is a device';
		elif [ -x "$name"  ]
		then
			echo 'it is a command' ;
		elif [ "$name" != " " ]
		then  
			usrname=`cat /etc/passwd |cut -d ':' -f 1 | grep $name`;
			# cannot add space next to the , because a3 is a var not a command
			#if id -u $name >/dev/null 2>&1;
			if [  "$usrname"  != "" ]
				then
					echo 'it is a user name.'
			else
				echo 'it is nothing' 
			fi
		else
			echo 'it is nothing'
		fi
	elif [ "$option" = "4" ]
	then
		echo "input a name!"
		read name
		echo 'the name you input is that: ';
		echo $name ;
		if [ ! -w "$name" ]
		then
			echo "it is un-writeable"
			chmod ug+w "$name"  
			if [ ! -w "$name" ]
			then
				echo "can't change to writeable "
			else
				echo "successfully change it to writeable"
			fi
		else
			echo "it is writeable"
		fi

	elif [ "$option" = "5" ]
	then
		echo "input a name!"
		read name
		if [ -x "$name" ]
		then 
			hexdump -C "$name"
		else
			  echo "can't excutable "
		fi

	elif [ "$option" = "6" ]
	then	
		echo "downloading file 1KB.zip\n------------------------------------"
ftp -nv<<!
open speedtest.tele2.net
user anonymous 0
quote PASV
binary
prompt
get 1KB.zip
close
bye
!
	elif [ "$option" = "7" ]
	then
	for processid in $(ps -ax | awk 'NR>1 {print $1}' ); do
    		depth=$(pstree -sA $processid | head -n1 | sed -e 's#-+-.*#---foobar#' -e 's#---*#\n#g' -eq | wc -l)
    		echo "$depth: $processid" > pstree.txt
	done
	sort -k1 -n pstree.txt
	tail -n 1 pstree.txt

	elif [ "$option" = "q" ]
	then
		echo "ok, will exit"
		exit

	else
		echo "invalid input, try again!"	
	fi;

echo "
1. List all (including hidden) files in /usr and its sub-directories in long format
2. List only hidden files in /usr and its sub-directories in long format
3. Input a name, report whether it is a file, a user, a device, a command, or nobody
4. Input a file name, if the file is "un-writeable", try to change it to "writeable" and report whether succeed
5. Read in a file name, show it in hexadecimal format if you have executable permission
6. Let '/usr/bin/ftp' automatically download "1KB.zip" from ftp://speedtest.tele2.net
7. *Display the process running on this computer who is the deepest-low in ‘pstree’
q. Quit "

done
