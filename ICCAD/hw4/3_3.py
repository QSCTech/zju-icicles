#!/usr/bin/env python
try:
    f = open("words","rt")
except IOError:
    print 'Could not open the file!'

longest=0
for line in f:
	for i in line:
		if ( i=='a' or i=='e' or i=='i' or i=='o' or i=='u'
		or i=='A' or i=='E' or i=='I' or i=='O' or i=='U'):
			flag = 0
			break
		else:
			flag = 1
	if flag==1:
		length = (len(line)-1) #there is a '\n' in 'line', so minus 1		
		if longest < length:
			longest = length
			longest_word = line
f.close()
print "The longest word without vowel is: " + longest_word + "Its length is: " + str(longest)

