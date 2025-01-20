#!/usr/bin/env python
try:
    f = open("words","rt")
except IOError:
    print 'Could not open the file!'

longest=0
for line in f:
	length = (len(line)-1) #there is a '\n' in 'line', so minus 1
	if longest < length:
		longest = length
		longest_word = line
f.close()
print "The longest word is: " + longest_word + "Its length is: " + str(longest)

