 3.11

Write the following queries in SQL, using the university schema.  这个好像在附录 .

a. Find the ID and name of each student who has taken at least one Comp. Sci. course; make sure there are no duplicate names in the result. 

```sql
select distinct student.id  student.name 
from course, student,takes
where course.dept_name = 'Comp. Sci.' and course.course_id =  takes.course_id  and takes.id = student.id
```

b. Find the ID and name of each student who has not taken any course offered before 2017. 

```sql
with course as 
    select year
     from takes
     where year < 2017
select student.id, student.name
from student, takes
where student.id = takes.id and takes.year not in course.year
```

c. For each department, find the maximum salary of instructors in that department. You may assume that every department has at least one instructor. 

```sql
with highestsalary (dept_name, maxSalary) as 
    select dept_name, max(salary)
    from instructor
    group by dept_name
select instructor.name, instructor.salary
from highestsalary, instructor
where highestsalary.salary = instructor.salary
```

d. Find the lowest, across all departments, of the per-department maximum salary computed by the preceding query.

```sql
with highestsalary (dept_name, maxSalary) as 
    select dept_name, max(salary)
    from instructor
    group by dept_name
with eachdeptHighest(name, salary) as 
    select instructor.name, instructor.salary
    from highestsalary, instructor
    where highestsalary.salary = instructor.salary
select name, min(salary)
from eachdeptHighest
```

3.15

Consider the bank database of Figure 3.18, where the primary keys are underlined. Construct the following SQL queries for this relational database. 

a. Find each customer who has an account at every branch located in “Brooklyn”.

For each customer, we need to check whether the set of all branches he has
an account contains the set of all branches in Brooklyn.
注意到 X – Y = Ø ⇔ X ⊆ Y

```sql
with locateBr(branch_name) as 
    select branch_name
    from branch
    where branch.branch_city = 'Brooklyn'
SELECT distinct S.customer_name 
FROM depositor as S
WHERE not exists (
     (SELECT branch_name
      FROM locateBr)
      EXCEPT
      (SELECT R.branch_name
       FROM depositor as T, account as R
       WHERE T.account_number = R.account_number and
             S.customer_name = T.customer_name ))
```

b. Find the total sum of all loan amounts in the bank. 

```sql
select sum(amount)
from loan
```

c. Find the names of all branches that have assets greater than those of at least one branch located in “Brooklyn”.

```sql
SELECT distinct branch_name 
      FROM branch 
      WHERE assets >   some
	             	(SELECT assets 
                     FROM branch 
                     WHERE branch_city = ‘Brooklyn’)

```



