#! /usr/bin/python

BOARD_SIZE = 8

def under_attack(col, queens):
    left = right = col

    for r, c in reversed(queens):
        left, right = left - 1, right + 1

	#for each loop here, the one more row upside is checked
	#totally 7 rows upper are checked
        #is c==col? (another queen is straight up)
        #is c==left? (another queen is diagonally left up)
        #is c==right (another queen is diagonally right up)
        if c in (left, col, right): 
            return True
    return False

def solve(n):
    if n == 0:
        return [[]]

    smaller_solutions = solve(n - 1)

    return [solution+[(n,i+1)]
        for i in xrange(BOARD_SIZE)
            for solution in smaller_solutions
                if not under_attack(i+1, solution)]

# try to run
# for answer in solve(1):
# for answer in solve(2):
# check with the results and get the idea of the program

for answer in solve(BOARD_SIZE):
    print answer

