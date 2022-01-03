#Python 3.7.5
#RTCG.py
#Random Test Case Generator
from random import randint
from functools import reduce,cmp_to_key
N = 50
K = 5
class person(object):
        def __init__(self,name,age,worth):
                self.name = name
                self.age = age
                self.worth = worth
        def stringify(self):
                return "{} {} {}\n".format(self.name,self.age,self.worth)
        def __sub__(self,rhs):
                if self.worth>rhs.worth:
                        return 1
                elif self.worth<rhs.worth:
                        return -1
                else:
                        if self.age<rhs.age:
                                return 1
                        elif self.age>rhs.age:
                                return -1
                        else:
                                if self.name<rhs.name:
                                        return 1
                                else:
                                        return -1
                                
Alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
Alphabet += [char.upper() for char in Alphabet]
Alphabet.append('_')
#Alphabet = [a-Z,_]
randomName = lambda n : reduce((lambda c1,c2:c1+c2),[Alphabet[randint(0,len(Alphabet)-1)] for i in range(n)])
randomAge = randomWorth = randint
randomPerson = lambda : person(randomName(8),randomAge(1,200),randomWorth(-100000,100000))


People = [randomPerson() for i in range(N)]

class query(object):
        def __init__(self,M,A1,A2):
           self.M = M
           self.A1 = A1
           self.A2 = A2
        def stringify(self):
                return "{} {} {}\n".format(self.M,self.A1,self.A2)
        def search(self,People):
                if self.A1<self.A2:
                        Amin = self.A1
                        Amax = self.A2
                else:
                        Amin = self.A2
                        Amax = self.A1
                
                peopleAged = [p for p in People if (Amin <=p.age and p.age<=Amax)]
                peopleAged.sort(key = cmp_to_key(lambda x,y:x-y),reverse = True)
                result = peopleAged[:self.M]
                if(len(result)==0):
                        return "None\n"
                else:
                        return reduce((lambda c1,c2:c1+c2),[p.stringify() for p in result])

randomQuery = lambda : query(randint(0,100),randint(1,200),randint(1,200))

Query = [randomQuery() for i in range(K)]

with open("input.txt","w+") as f:
        f.write("{} {}\n".format(N,K))
        for P in People:
                f.write(P.stringify())
        for Q in Query:
                f.write(Q.stringify())

with open("output.txt","w+") as f:
        for index,Q in enumerate(Query):
                f.write("Case #{}:\n{}".format(index,Q.search(People)))

