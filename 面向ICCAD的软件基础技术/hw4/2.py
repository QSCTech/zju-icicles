#!/usr/bin/env python
import re
try:
    f = open("8queen.out","rt")
except IOError:
    print('Could not open the file!')

number = [[[] for j in range(8)] for i in range(92)]
pattern = re.compile(r'\d+')
index = 0
# get number
for line in f:
	temp = line.replace("\n","")	
	count = 0
	col = 0
	for i in re.findall(pattern,temp):		
		number[index][col].append(int(i))
		count += 1
		if count%2==0:
			col += 1
	index += 1
f.close()
for n in number:
	# get 7 changes
	eq = [[[] for j in range(8)] for i in range(7)]					
	for i in range(8):	
		# (a,b) -> (a,9-b)
		eq[0][i].append(n[i][0])
		eq[0][i].append(9-n[i][1])
		# (a,b) -> (9-a,b)
		eq[1][i].append(9-n[i][0])
		eq[1][i].append(n[i][1])
		# (a,b) -> (9-b,a)
		eq[2][i].append(9-n[i][1])
		eq[2][i].append(n[i][0])				
		# (a,b) -> (9-a,9-b)
		eq[3][i].append(9-n[i][0])
		eq[3][i].append(9-n[i][1])
		# (a,b) -> (b,9-a)
		eq[4][i].append(n[i][1])
		eq[4][i].append(9-n[i][0])
		# (a,b) -> (b,a)
		eq[5][i].append(n[i][1])
		eq[5][i].append(n[i][0])
		# (a,b) -> (9-b,9-a)
		eq[6][i].append(9-n[i][1])
		eq[6][i].append(9-n[i][0])														
	# sort and find the same 	
	temp = eq[0]
	if temp in number:
		number.remove(temp)

	for i in range(1,7):
		for j in range(8):
			first = eq[i][j][0]
			second = eq[i][j][1]
			if   first==1:
				temp[0][1] = second			
			elif first==2:
				temp[1][1] = second
			elif first==3:
				temp[2][1] = second
			elif first==4:
				temp[3][1] = second
			elif first==5:
				temp[4][1] = second
			elif first==6:
				temp[5][1] = second
			elif first==7:
				temp[6][1] = second			
			else:
				temp[7][1] = second				
		if temp in number and temp != n:
			number.remove(temp)								
print "There are totally " + str(len(number)) + " solutions."
print "They are: "

def get_pos_lst(l):
    i = 5
    tt = []
    while(i<64):
        tt.append(l[i])
        i += 8
    return tt


for i in number:
	# print i
	line = str(i)
	lst = get_pos_lst(line)
	print lst
	for j in range(8):
		for k in range(8):
			if (int(lst[j])==k+1):
				print 'Q',
			else:
				print '-',
		print 