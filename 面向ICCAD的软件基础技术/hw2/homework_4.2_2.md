# Please CAREFULLY read the questions and follow instructions to answer.

## Problem 1.
## Write a shell script (must use vi) that displays the following menu and prompts for one-character input (i.e., '1' - '6' or 'q') to invoke a menu option, as shown.
### 1. List all files in current directory and sub-directories in long format
### 2. List all hidden files in current directory and sub-directories in long format
### 3. Read in a name, report whether it is a file, a user, a device, a command, or nobody
### 4. For a file found early in 1, show it in hexadecimal format if you have executable permission
### 5. Display all processes running on this computer whose ancestor is a process of specified PID
### 6. Let '/usr/bin/ftp' automatically download "demo_inout.c" from our course ftp site
### q. Quit
*The program should allow the user to try any option any number of times and show the above menu every time after an operation, and it would quit until user gives option q as input. Option (3) and option (5) prompt the user to input a file name first.*

## Problem 2.
### After downloading "demo_inout.c" from our ftp site, try to build by "gcc -o demo_inout demo_inout.c", run the resulted executable "demo_inout", read input from a file and send two outputs to two separate files. Figure out the mechanism for stdin, stdout and stderr redirection.

## Problem 3.
### Write a shell script 'pingsort' (must use vi) that takes a whole list of host names as command line arguments. The script pings each host 10 times and reports the average responding time of each host in the order of the delays (unreachable addresses are sorted by their IP addresses).

The following is a running sample,

$./pingsort wikipedia.org www.sina.com.cn www.zju.edu.cn www.cnn.com www.google.com

www.zju.edu.cn @ 10.203.4.199 @ 6.674 ms
www.sina.com.cn @ 67.172.201.194 @ 11.642 ms
wikipedia.org @ 198.34.26.96 @ 192.652 ms
www.cnn.com @ 151.101.16.73 is unreachable
www.google.com @ 93.46.8.89 is unreachable

*The program should be able to take unlimited number of arguments (not only 5 sites as in the sample above).*

## Problem 4. (OPTIONAL)
### Visit http://www.bing.com, and download a cool background image from this site. (yes, manually) Then, read manuals for command "wget", command "sed" or "awk" and command "cron". With the help of these commands and other utilities we have learned, try to write some shell programs which can be used to automatically visit www.bing.com every night to download a background image.
