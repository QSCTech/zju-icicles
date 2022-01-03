#! /bin/bash

# ----------------------------------------------------------------
# " author : Lin Juyi , college of ISEE, ZHEJIANG UNIVERSITY 1263810658@qq.com"
# " latest update time : 2020/ 12/7 "
# " created time : 2020/11/14  for ICCAD class, homework 4_4_3, problem 3  "
# Usage:
# ./pingsort + websites
# ----------------------------------------------------------------
# rm the file that generate before.
rm	 pingsort_1.txt pingsort_2.txt pingsort_3.txt pingsort_4.txt 
for args in $@
# repeat for every input website 
do	
	# ping 5 times
	ping -c 5 $args | cut -d '(' -f2 | cut -d ')' -f1 | cut -d '/' -f 5 > pingsort_1.txt
	# get the hostname and save to variable a
	a=`sed -n 1p pingsort_1.txt`
	# get the speed and save to variable b
	cut -d ' ' -f 4 pingsort_1.txt > pingsort_2.txt	
	b=`awk 'NF{a=$0}END{print a}' pingsort_2.txt`
	# if b=0, the website is unreachable.
	c='0'
	if [ "$b" = "$c" ]
	then
		echo "$args $a" >> pingsort_3.txt
	else 
		echo "$args $a $b"	>>  pingsort_4.txt
	fi
done
  	sort -k 3 -n -u pingsort_4.txt > pingsort5.txt
	printf " %-10s @ %-10s @ %-10s ms \n" $(cat pingsort5.txt)
	printf "\n"
	printf " %-10s @ %-10s is unreachable \n" $(cat pingsort_3.txt)
#  output pingsort4  then pingsort 3
	