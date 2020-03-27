#!/usr/bin/env python
try:
    f = open("words","rt")
except IOError:
    print 'Could not open the file!'

count = 0
for line in f:
	count += 1

f.close()

print count
