2.12

Consider the bank database of Figure 2.18. Assume that branch names and customer names uniquely identify branches and customers, but loans and accounts can be associated with more than one customer. 

a. What are the appropriate primary keys? 

It must contain a unique value for each row of data. It cannot contain null values.

b. Given your choice of primary keys, identify appropriate foreign keys.

branch(**branch name**, branch city, assets) 

customer (**ID, customer name**, customer street, customer city)

 loan (**loan number**, branch name, amount) 

borrower (ID, **loan number**) 

account (**account number**, branch name, balance) 

depositor (ID, **account number**)

2.14

Consider the employee database of Figure 2.17. Give an expression in the relational algebra to express each of the following queries: 

a. Find the ID and name of each employee who works for “BigBank”. 

b. Find the ID, name, and city of residence of each employee who works for “BigBank”. 

c. Find the ID, name, street address, and city of residence of each employee who works for “BigBank” and earns more than $10000. 

d. Find the ID and name of each employee in this database who lives in the same city as the company for which she or he works.

![image-20220321235952868](C:\Users\12638\AppData\Roaming\Typora\typora-user-images\image-20220321235952868.png)



2.15

Consider the bank database of Figure 2.18. Give an expression in the relational algebra for each of the following queries: 

a. Find each loan number with a loan amount greater than $10000. 

b. Find the ID of each depositor who has an account with a balance greater than $6000. 

c. Find the ID of each depositor who has an account with a balance greater than $6000 at the “Uptown” branch.

![image-20220322000006120](C:\Users\12638\AppData\Roaming\Typora\typora-user-images\image-20220322000006120.png)