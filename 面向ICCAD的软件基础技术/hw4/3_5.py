#!/usr/bin/env python
try:
    f = open("words","rt")
except IOError:
    print 'Could not open the file!'
str = []
for line in f:
	str.append(line.replace("\n",""))
count = 0
for s in str:
	sub1 = s + 's'
	sub2 = s + '\'s'
	if sub1 or sub2 in str:
		print s
		# count += 1
		# print count
		if sub1 in str:
			print sub1
			str.remove(sub1)
		if sub2 in str:
			print sub2
			str.remove(sub2)
