#!/usr/bin/env python
import sys

def get_pos_lst(l):
    i = 5
    tt = []
    while(i<64):
        tt.append(l[i])
        i += 8
    return tt

try:
    f = open("8queen.out","rt")
except IOError:
    print 'getting data from stdin...'
    f = sys.stdin

for line in f:
    lst = get_pos_lst(line)
    print lst

    for j in range(8):
        for k in range(8):
            if (int(lst[j])==k+1):
                print 'Q',
            else:
                print '-',
        print 

if f is not sys.stdin:
    f.close()
